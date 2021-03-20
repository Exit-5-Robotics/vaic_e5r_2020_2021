#include "vex.h"

using namespace vex;

const int rollerDistance = 400;
const int intakeDriveSpeed = 10;

void turnTo( float dest_heading, int vel ) {
  
  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  float change = dest_heading - (current_heading*180/M_PI);
  change = change > 0 ? change : change + 360;

  if (change < 180) {
    Brain.Screen.printAt(10, 100, "Right");
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  } else {
    Brain.Screen.printAt(10, 120, "Left");
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  }
  
}

void goTo( float dest_x, float dest_y, float dest_heading ) {   

  float start_x, start_y, start_heading, current_x, current_y, current_heading;
  link.get_local_location(start_x, start_y, start_heading);
  // turnTo(dest_heading, 30);
  link.get_local_location(start_x, start_y, start_heading);

  // convert units to inches and degrees
  start_x /= 25.4;
  start_y /= 25.4;
  start_heading *= 180/M_PI;
  start_heading += 180;

  float change_x = dest_x - start_x;
  float change_y = dest_y - start_y;

  int turnToAngle = (int)(90 - atan((double)change_y/(double)change_x)*180/M_PI)%360;
  if ((change_x*change_y > 0 && change_y <0) || (change_x*change_y < 0 && change_y > 0) || (change_x < 0 && change_y == 0)) turnToAngle += 180;

  // turnTo(turnToAngle, 5);
  // LeftDrive.setVelocity(pow(drivetrainForwardBackward, 2) / 1.2*drivetrainForwardBackward, percent);
  // RightDrive.setVelocity(pow(drivetrainForwardBackward, 2) / 1.2*drivetrainForwardBackward, percent);
  // robotDrive.driveFor(sqrt((double)pow(change_x, 2) + (double)pow(change_y,2)), vex::distanceUnits::in, 5, vex::velocityUnits::pct);
  driveAngle(turnToAngle, 30);
  
  current_x = start_x, current_y = start_y, current_heading = start_heading;
  while(abs((int)current_x - (int)dest_x) > 10) {
    link.get_local_location(current_x, current_y, current_heading);
  }
  robotDrive.stop();
  
  // turnTo(dest_heading, 5);

}

void intake( int speed ) {
  while (ballThree.value(analogUnits::mV) > 3300) {
    robotDrive.drive(fwd, speed, vex::velocityUnits::pct);
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  robotDrive.stop();
  intakeWheels.spinFor(fwd, 720, degrees, 60, vex::velocityUnits::pct);
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

int adjustHold( int speed ) {
  while (ballZero.value(analogUnits::mV) > 3400) {
    botRoller.spin(fwd, speed, vex::velocityUnits::pct);
    topRoller.spin(fwd, speed, vex::velocityUnits::pct);
  }
  botRoller.stop();
  topRoller.stop();
  return 0;
}

int testMovement() { // just for testing
  // task::sleep(2000);
  // driveAngleFor(10, 330, 15);
  // // descore();
  // frontLeftWheel.spinFor(fwd, 800, rotationUnits::deg, 30, velocityUnits::pct, false);
  // frontRightWheel.spinFor(fwd, 800, rotationUnits::deg, 30, velocityUnits::pct, false);
  // backLeftWheel.spinFor(fwd, 800, rotationUnits::deg, 30, velocityUnits::pct, false);
  // backRightWheel.spinFor(fwd, 800, rotationUnits::deg, 30, velocityUnits::pct);
  // frontLeftWheel.spinFor(fwd, 800, rotationUnits::deg, 60, velocityUnits::pct, false);
  // frontRightWheel.spinFor(fwd, 800, rotationUnits::deg, 60, velocityUnits::pct, false);
  // backLeftWheel.spinFor(fwd, 800, rotationUnits::deg, 60, velocityUnits::pct, false);
  // backRightWheel.spinFor(fwd, 800, rotationUnits::deg, 60, velocityUnits::pct);
  this_thread::sleep_for(20000);
  
  while (true) {
    float current_x, current_y, current_heading;
    link.get_local_location(current_x, current_y, current_heading);
    // adjustHold(20);
    if (current_x != 0) {

      task::sleep(2000);
      goTo(-40, -40, 180);
      // driveAngleAbs(45, 30);
      // redIsolation();
      task::sleep(10000);
    }

    this_thread::sleep_for(16);
  }
  return 0;
}