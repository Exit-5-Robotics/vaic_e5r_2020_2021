#include "vex.h"

using namespace vex;

const int rollerDistance = 400;
const int intakeDriveSpeed = 10;


void driveAngle( int angleToDrive, int speed ) {
  // drive at an angle relative to the current angle of the robot
  int measureAngle = (angleToDrive + 45)%360;
  int tempAngle;
  float rightSpeed, leftSpeed;
  switch (measureAngle/90) {
    case 0:
      tempAngle = 90 - measureAngle;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(fwd, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(fwd, leftSpeed, velocityUnits::pct);
      // both L and R are positive
      break;
    case 1:
      // R is positive, L is negative
      tempAngle = measureAngle - 90;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(fwd, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(reverse, leftSpeed, velocityUnits::pct);
      break;
    case 2:
      // both L and R are negative
      tempAngle = 270 - measureAngle;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(reverse, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(reverse, leftSpeed, velocityUnits::pct);
      break;
    default:
      // L is positive, R is negative
      tempAngle = measureAngle - 270;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(reverse, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(fwd, leftSpeed, velocityUnits::pct);
      break;
  }
}

void driveAngleAbs( int angleToDrive, int speed ) {
  // drive at an absolute angle
  // get starting location and heading (mainly just heading)
  float start_x, start_y, start_heading;
  link.get_local_location(start_x, start_y, start_heading);
  // convert to degrees
  start_heading *= 180/M_PI;
  start_heading += 180;

  // find angle to drive at relative to current heading
  int relativeDriveAngle = (angleToDrive - (int)start_heading)%360;
  if (relativeDriveAngle < 0) relativeDriveAngle += 360;
  
  driveAngle(relativeDriveAngle, speed);
}

void driveAngleFor( int dist, int angleToDrive, int speed ) {
  // drive at an angle for a distance in inches relative to current angle of robot
  int degreesDrive = dist*47;
  int currentRotation = robotDrive.rotation(deg);
  driveAngle(angleToDrive, speed);
  while (sqrt(pow(rightDiagDrive.rotation(deg),2)+pow(leftDiagDrive.rotation(deg),2))-currentRotation < degreesDrive);
  robotDrive.stop();
}

void driveAngleForAbs( int dist, int angleToDrive, int speed ) {
  // drive at an absolute angle for a distance in inches
  float start_x, start_y, start_heading;
  link.get_local_location(start_x, start_y, start_heading);
  // convert to degrees
  start_heading *= 180/M_PI;
  start_heading += 180;

  // find angle to drive at relative to current heading
  int relativeDriveAngle = (angleToDrive - (int)start_heading)%360;
  
  driveAngleFor(dist, relativeDriveAngle, speed);
}

int turnTo( float dest_heading, int vel ) {
  
  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  float change = dest_heading - (current_heading*180/M_PI) + 180;
  change = change > 0 ? change : change + 360;

  if (change < 180) {
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct, false);
    while (robotDrive.isTurning()) {
      link.get_local_location(current_x, current_y, current_heading);
      if (abs((int)dest_heading - (int)current_heading + 180) < 5) {
        robotDrive.stop();
        return 0;
      }
    }
  } else {
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct, false);
    while (robotDrive.isTurning()) {
      link.get_local_location(current_x, current_y, current_heading);
      if (abs((int)dest_heading - (int)current_heading + 180) < 5) {
        robotDrive.stop();
        return 0;
      }
    }
  }
  return 0;
}

void goTo( float dest_x, float dest_y, float dest_heading ) {   

  turnTo(dest_heading, 30);

  float start_x, start_y, start_heading, current_x, current_y, current_heading;
  link.get_local_location(start_x, start_y, start_heading);

  // convert units to inches and degrees
  start_x /= 25.4;
  start_y /= 25.4;
  start_heading *= 180/M_PI;
  start_heading += 180;

  float change_x = dest_x - start_x;
  float change_y = dest_y - start_y;

  int driveToAngle = (int)(90 - atan((double)change_y/(double)change_x)*180/M_PI)%360;

  // Adjusts to go to -x direction of field
  if ((change_x*change_y > 0 && change_y <0) || (change_x*change_y < 0 && change_y > 0) || (change_x < 0 && change_y == 0)) driveToAngle += 180;

  current_x = start_x, current_y = start_y, current_heading = start_heading;
  driveAngleAbs(driveToAngle, 30);
  dest_x *= 25.4, dest_y *= 25.4;
  while(abs((int)current_x - (int)dest_x) > 50) link.get_local_location(current_x, current_y, current_heading);
  robotDrive.stop();

  if (abs((int)current_y - (int)dest_y) > 50) {
    int directionY = (current_y - dest_y) ? 0 : 1;

    driveAngleAbs(180*directionY, 30);
    while(abs((int)current_y - (int)dest_y) > 50) link.get_local_location(current_x, current_y, current_heading);
    robotDrive.stop();
  }

  turnTo(dest_heading, 30);
}

void intake( int speed ) {
  while (ballThree.value(analogUnits::mV) > 3300) {
    robotDrive.drive(fwd, speed, vex::velocityUnits::pct);
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  robotDrive.stop();
  intakeWheels.spinFor(fwd, 720, degrees, 60, vex::velocityUnits::pct);
}

void intakeNoDrive() {
  while (ballThree.value(analogUnits::mV) > 3300) {
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  intakeWheels.stop();
}

void outtake() {
  // leftIntake.spinFor(rev, double rotation, vex::rotationUnits::deg, double velocity, velocityUnits units_v);
  // rightIntake.spinFor(rev, double rotation, vex::rotationUnits::deg, double velocity, velocityUnits units_v);
}

void score() {
  // ONLY RUN IF THE DESIRED SCORED BALL IS IN POSITION 3/ARRAY INDEX 0
  botRoller.spinFor(fwd, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
  topRoller.spinFor(fwd, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}

void poop() {
  // ONLY RUN IF THE DESIRED POOPED BALL IS IN POSITION 2/ARRAY INDEX 1
  botRoller.spinFor(fwd, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct, false);
  topRoller.spinFor(reverse, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}

void descore() {
  while(!goal.pressing()) robotDrive.drive(fwd, 30, vex::velocityUnits::pct);
  intake(intakeDriveSpeed);
  robotDrive.driveFor(reverse, 10, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
}

void pickUp( float dist ) {
  // TODO
  intake(intakeDriveSpeed);
  robotDrive.driveFor(fwd, dist, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
}

int adjustHold() {
  while (ballZero.value(analogUnits::mV) > 3400) {
    botRoller.spin(fwd, 100, vex::velocityUnits::pct);
    topRoller.spin(fwd, 100, vex::velocityUnits::pct);
  }
  botRoller.stop();
  topRoller.stop();
  return 0;
}

int centerGoal() {
  int goalX = 160;
  int directionDrive, diff, currentBox = 5;

  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  if (local_map.boxnum > 0) {
    for(int i=0;i<4;i++ ) {
      if( i < local_map.boxnum ) {
        if (local_map.boxobj[i].classID == 2) currentBox = i;
        break;
      }
    }
    if (currentBox != 5) {
      diff = goalX - local_map.boxobj[currentBox].x;
      while (abs(diff) > 5) {
        jetson_comms.get_data( &local_map );
        for(int i=0;i<4;i++ ) {
          if( i < local_map.boxnum ) {
            if (local_map.boxobj[i].classID == 2) currentBox = i;
            break;
          }
        }
        diff = goalX - local_map.boxobj[currentBox].x;
        directionDrive = (diff > 0) ? 0 : 180;
        driveAngle(90+directionDrive, 10);
      }
    }
  }

  return 0;
}

int moveDistSensor( int direc ) {
  distMotor.spinFor(direc*300, degrees, 100, velocityUnits::pct);
  return direc;
}

int testMovement() { // just for testing
  float current_x, current_y, current_heading;
  
  while (true) {
    link.get_local_location(current_x, current_y, current_heading);

    if (current_x != 0) {
      task::sleep(15000);
      redIsolation();
    }

    // if (current_heading != 0) {
    //   centerGoal();
    // }

    this_thread::sleep_for(16);
  }
  return 0;
}