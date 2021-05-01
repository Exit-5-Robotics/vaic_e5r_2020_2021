#include "vex.h"

using namespace vex;

void bumpedIntoSomething( void ) {
  if (tilt.acceleration(axisType::xaxis)==0 /*&& distPosition==UP && dist.objectDistance(distanceUnits::mm)<200*/ && driving==true) {
    robotDrive.stop();
    // pause everything for 5 sec
    // robotDrive.driveFor(reverse, 10, inches, 30, velocityUnits::pct); // fix to whatever direction i need to drive
  }
}

void driveAway( void ) {
  if (testChange() == false && driving == false /*&& robotBusy == false*/){
    // driveAngle
    ;
  }
}

void driveAngle( int angleToDrive, int speed ) {
  // drive at an angle relative to the current angle of the robot
  int measureAngle = (angleToDrive + 405)%360;
  int tempAngle;
  float rightSpeed, leftSpeed;
  driving = true;
  Brain.Screen.printAt(10, 120, "measureangle:%d", measureAngle);
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
  static MAP_RECORD botMap;
  jetson_comms.get_data( &botMap );

  // drive at an absolute angle
  // get starting location and heading (mainly just heading)
  // convert to degrees

  // find angle to drive at relative to current heading
  driving = true;
  int relativeDriveAngle = (angleToDrive - (int)(botMap.pos.az*180/M_PI))%360;
  Brain.Screen.printAt(10, 140, "%d", relativeDriveAngle);
  if (relativeDriveAngle < 0) relativeDriveAngle += 360;
  
  driveAngle(relativeDriveAngle, speed);
}

void driveAngleFor( int dist, int angleToDrive, int speed ) {
  // drive at an angle for a distance in inches relative to current angle of robot
  driving = true;
  int degreesDrive = dist*47;
  robotDrive.setRotation(0, rotationUnits::deg);
  rightDiagDrive.setRotation(0, rotationUnits::deg);
  leftDiagDrive.setRotation(0, rotationUnits::deg);
  int currentRotation = robotDrive.rotation(deg);
  driveAngle(angleToDrive, speed);
  while (sqrt(pow(rightDiagDrive.rotation(deg),2)+pow(leftDiagDrive.rotation(deg),2))-currentRotation < degreesDrive) {
    Brain.Screen.printAt(300, 40, "driving");
  }
  robotDrive.stop();
    Brain.Screen.printAt(300, 40, "stopped driving");
}

void driveAngleForAbs( int dist, int angleToDrive, int speed ) {
  // drive at an absolute angle for a distance in inches
  driving = true;

  // find angle to drive at relative to current heading
  int relativeDriveAngle = (angleToDrive - (int)local_heading)%360;
  
  driveAngleFor(dist, relativeDriveAngle, speed);
}

int turnTo( float dest_heading, int vel ) {
  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  float change = dest_heading - (current_heading*180/M_PI);
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

void goToX( float dest_x, float dest_y, float dest_heading ) {
  turnTo(dest_heading, 30);
  static MAP_RECORD thisMap;
  jetson_comms.get_data(&thisMap);

  float start_x, start_y, start_heading, current_x, current_y, current_heading;
  start_x = thisMap.pos.x;
  start_y = thisMap.pos.y;
  start_heading = thisMap.pos.az;

  // convert units to inches and degrees
  start_x /= 25.4;
  start_y /= 25.4;
  start_heading *= 180/M_PI;
  Brain.Screen.printAt(10, 60, "%.2f %.2f %.2f", start_x, start_y, start_heading);

  float change_x = dest_x - start_x;
  float change_y = dest_y - start_y;

  int driveToAngle = (int)(90 - atan2(change_y, change_x)*180/M_PI)%360;
  Brain.Screen.printAt(300, 60, "%d", driveToAngle);

  current_x = start_x, current_y = start_y, current_heading = start_heading;
  driveAngleAbs(driveToAngle, 30);
  Brain.Screen.printAt(10, 80, "Driving");
  dest_x *= 25.4, dest_y *= 25.4, current_x*=25.4, current_y*=25.4;
  int test_x;
  while(abs((int)current_x - (int)dest_x) > 50) {
    jetson_comms.get_data(&thisMap);
    test_x = current_x;
    current_x = thisMap.pos.x;
    current_y = thisMap.pos.y;
    current_heading = thisMap.pos.az;

    Brain.Screen.printAt(10, 60, "%.2f %.2f %.2f", current_x/25.4, current_y/25.4, current_heading*180/M_PI);
    if (current_x == test_x) {
      robotDrive.stop();
      Brain.Screen.printAt(300, 20, "waiting");
    }
  }
  robotDrive.stop();

  turnTo(dest_heading, 30);
}

void goToY( float dest_x, float dest_y, float dest_heading ) {
  turnTo(dest_heading, 30);
  static MAP_RECORD thisMap;
  jetson_comms.get_data(&thisMap);

  float start_x, start_y, start_heading, current_x, current_y, current_heading;
  start_x = thisMap.pos.x;
  start_y = thisMap.pos.y;
  start_heading = thisMap.pos.az;

  // convert units to inches and degrees
  start_x /= 25.4;
  start_y /= 25.4;
  start_heading *= 180/M_PI;
  Brain.Screen.printAt(10, 60, "%.2f %.2f %.2f", start_x, start_y, start_heading);

  float change_x = dest_x - start_x;
  float change_y = dest_y - start_y;

  int driveToAngle = (int)(90 - atan2(change_y, change_x)*180/M_PI)%360;
  Brain.Screen.printAt(300, 60, "%d", driveToAngle);

  current_x = start_x, current_y = start_y, current_heading = start_heading;
  driveAngleAbs(driveToAngle, 30);
  Brain.Screen.printAt(10, 80, "Driving");
  dest_x *= 25.4, dest_y *= 25.4, current_x*=25.4, current_y*=25.4;
  int test_y;
  while(abs((int)current_y - (int)dest_y) > 50) {
    jetson_comms.get_data(&thisMap);
    test_y = current_y;
    current_x = thisMap.pos.x;
    current_y = thisMap.pos.y;
    current_heading = thisMap.pos.az;
    
    Brain.Screen.printAt(10, 60, "%.2f %.2f %.2f", current_x/25.4, current_y/25.4, current_heading*180/M_PI);
    if (current_y == test_y) {
      robotDrive.stop();
      Brain.Screen.printAt(300, 20, "waiting");
    }
  }
  robotDrive.stop();

  turnTo(dest_heading, 30);
}