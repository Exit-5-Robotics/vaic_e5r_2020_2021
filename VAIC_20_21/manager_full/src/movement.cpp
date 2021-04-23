#include "vex.h"

using namespace vex;

const int rollerDistance = 400;
const int intakeDriveSpeed = 10;


void stopDriving( void ) {
  robotDrive.stop();
  driving = false;
}

void lookAround( void ) {
  static int opponentScored = 0;
  robotDrive.turnFor(right, 360, degrees, 20, velocityUnits::pct);
  while(opponentScored == 0) {
    for (int i=0; i<local_map.boxnum; i++) {
      std::string ballPos = getBallPosition(local_map.boxobj[i]);  // fix please 
      ballsOnField.push_back({local_map.boxobj[i].classID, ballPos});
    }
  }
}

void driveAngle( int angleToDrive, int speed ) {
  // drive at an angle relative to the current angle of the robot
  int measureAngle = (angleToDrive + 405)%360;
  int tempAngle;
  float rightSpeed, leftSpeed;
  driving = true;
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
  // convert to degrees

  // find angle to drive at relative to current heading
  driving = true;
  int relativeDriveAngle = (angleToDrive - (int)local_heading)%360;
  if (relativeDriveAngle < 0) relativeDriveAngle += 360;
  
  driveAngle(relativeDriveAngle, speed);
}

void driveAngleFor( int dist, int angleToDrive, int speed ) {
  // drive at an angle for a distance in inches relative to current angle of robot
  driving = true;
  int degreesDrive = dist*47;
  int currentRotation = robotDrive.rotation(deg);
  driveAngle(angleToDrive, speed);
  while (sqrt(pow(rightDiagDrive.rotation(deg),2)+pow(leftDiagDrive.rotation(deg),2))-currentRotation < degreesDrive);
  robotDrive.stop();
}

void driveAngleForAbs( int dist, int angleToDrive, int speed ) {
  // drive at an absolute angle for a distance in inches
  driving = true;

  // find angle to drive at relative to current heading
  int relativeDriveAngle = (angleToDrive - (int)local_heading)%360;
  
  driveAngleFor(dist, relativeDriveAngle, speed);
}

int turnTo( float dest_heading, int vel ) {
  driving = true;

  float change = dest_heading - local_heading;
  change = change > 0 ? change : change + 360;

  if (change < 180) {
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct, false);
    while (robotDrive.isTurning()) {
      if (abs((int)dest_heading - (int)local_heading) < 5) {
        robotDrive.stop();
        return 0;
      }
    }
  } else {
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct, false);
    while (robotDrive.isTurning()) {
      if (abs((int)dest_heading - (int)local_heading) < 5) {
        robotDrive.stop();
        return 0;
      }
    }
  }
  return 0;
}

void goTo( float dest_x, float dest_y, float dest_heading ) {   
  driving = true;

  turnTo(dest_heading, 30);
  // convert units to inches and degrees

  float change_x = dest_x - local_x;
  float change_y = dest_y - local_y;

  int driveToAngle = (int)(90 - atan((double)change_y/(double)change_x)*180/M_PI)%360;

  // Adjusts to go to -x direction of field
  if ((change_x*change_y > 0 && change_y <0) || (change_x*change_y < 0 && change_y > 0) || (change_x < 0 && change_y == 0)) driveToAngle += 180;

  driveAngleAbs(driveToAngle, 30);
  dest_x *= 25.4, dest_y *= 25.4;
  while(abs((int)local_x - (int)dest_x) > 50);
  robotDrive.stop();

  if (abs((int)local_y - (int)dest_y) > 50) {
    int directionY = (local_y - dest_y) ? 0 : 1;

    driveAngleAbs(180*directionY, 30);
    while(abs((int)local_y - (int)dest_y) > 50);
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

void pickUpClosest( std::string ballPos ) {
  // TODO
  goTo(stringToX(ballPos), stringToY(ballPos), local_heading); // ADJUST FOR ROBOT ADJUST FOR ROBOT ADJUST FOR ROBOT ADJUST FOR ROBOT
  // intake(intakeDriveSpeed);
  // robotDrive.driveFor(fwd, dist, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
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

int centerBall( fifo_object_box boxObj ) {
  // back up to 20 inches
  while (boxObj.depth/25.4 < 20)
    driveAngle(180, 20);
  stopDriving();
  Brain.Screen.printAt(160, 40, "%d", boxObj.x);

  // center by driving sideways
  while (boxObj.x > 190 || boxObj.x < 170) {
    driveAngle((boxObj.x-180)/abs(boxObj.x-180)*90, (int)(abs(boxObj.x - 180)/2));
    Brain.Screen.printAt(160, 80, "%d", boxObj.x/abs(boxObj.x)*90);
    Brain.Screen.printAt(160, 40, "%d", boxObj.x);
    Brain.Screen.printAt(160, 120, "%d", (int)(boxObj.depth/25.4));
  }
  stopDriving();

  return 0;
}

int centerGoal() {
  int goalX = 160;
  int directionDrive, diff, currentBox = 5;

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
  distMotor.spinFor(direc*-300, degrees, 100, velocityUnits::pct);
  return direc;
}

void distSensorControl( void ) {
  int objDistance = dist.objectDistance(distanceUnits::mm);
  int distPosition = 1;
  while (true) {
    objDistance = dist.objectDistance(distanceUnits::mm);
    if (objDistance < 200 && distPosition == -1) {
      distPosition = moveDistSensor(UP);
      this_thread::sleep_for(5000);
    } else if (objDistance > 200 && distPosition == 1) { // issue because when it goes up, does not see object any more
      distPosition = moveDistSensor(DOWN);
    } else {
      distMotor.stop();
    }
  }
}

int testMovement() { // just for testing

  // intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  
  while(true) {
    robotDrive.drive(fwd, 10, velocityUnits::pct);
    Brain.Screen.printAt(10, 20, "%f", tilt.acceleration(axisType::xaxis));
  }
  // robotDrive.stop();
  
  // while (ballThree.value(analogUnits::mV) > 3300) robotDrive.drive(fwd, 5, velocityUnits::pct);
  
  
  while (true) {
    // if (local_x != 0) {
    //   task::sleep(15000);
    //   redIsolation();
    // }

    // if (local_heading != 0) {
    //   centerGoal();
    // }

    this_thread::sleep_for(16);
  }
  return 0;
}