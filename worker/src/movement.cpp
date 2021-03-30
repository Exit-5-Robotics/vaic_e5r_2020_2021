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

void turnTo( float dest_heading, int vel ) {
  
  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  float change = dest_heading - (current_heading*180/M_PI) + 180;
  change = change > 0 ? change : change + 360;

  if (change < 180) {
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  } else {
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  }
  
}

void goTo( float dest_x, float dest_y, float dest_heading ) {   

  float start_x, start_y, start_heading, current_x, current_y, current_heading;
  link.get_local_location(start_x, start_y, start_heading);
  turnTo(dest_heading, 30);

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

  driveAngleAbs(driveToAngle, 30);
  
  current_x = start_x, current_y = start_y, current_heading = start_heading;
  dest_x *= 25.4, dest_y *= 25.4;
  while(abs((int)current_x - (int)dest_x) > 100) link.get_local_location(current_x, current_y, current_heading);
  Brain.Screen.printAt(10, 40, "toward pos");
  int toward_pos = current_y - dest_y > 0 ? 1 : -1;
  while(abs((int)current_y - (int)dest_y) > 50) {
    link.get_local_location(current_x, current_y, current_heading);
    driveAngleAbs(toward_pos*180, 30);
  }
  pause();
  turnTo(dest_heading, 30);
}

void poop() {
  intake.spinFor(fwd, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct, false);
  roller.spinFor(reverse, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}