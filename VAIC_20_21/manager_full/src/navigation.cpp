#include "vex.h"

using namespace vex;

void bumpedIntoSomething( void ) {
  if (tilt.acceleration(axisType::xaxis)==0 && distPosition==UP && dist.objectDistance(distanceUnits::mm)<200 && driving==true) {
    robotDrive.stop();
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
