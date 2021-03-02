#include "vex.h"

using namespace vex;


void turnTo( float dest_heading, int vel ) {
  
  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  float change = dest_heading - (current_heading*180/M_PI + 180);
  change = change > 0 ? change : change + 360;

  if (change < 180) {
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  } else {
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  }
  
}

void goTo( float dest_x, float dest_y, float dest_heading ) {

  float start_x, start_y, start_heading;
  link.get_local_location(start_x, start_y, start_heading);

  // convert units to inches and degrees
  start_x /= 25.4;
  start_y /= 25.4;
  start_heading *= 180/M_PI + 180;

  float change_x = dest_x - start_x;
  float change_y = dest_y - start_y;
  Brain.Screen.printAt(10, 20, "change x: %f", change_x);
  Brain.Screen.printAt(10, 40, "change y: %f", change_y);

  double turnToAngle = (90 - atan((double)change_y/(double)change_x)*180/M_PI);
  Brain.Screen.printAt(10, 60, "turn to: %f", turnToAngle);

  turnTo(turnToAngle, 5);
  
  robotDrive.driveFor(sqrt((double)pow(change_x, 2) + (double)pow(change_y,2)), vex::distanceUnits::in, 5, vex::velocityUnits::pct);
  
  turnTo(dest_heading, 5);

}

void intake() {
  while (ball.value(analogUnits::mV) > 3300) {
    robotDrive.drive(fwd, 10, vex::velocityUnits::pct);
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  robotDrive.stop();
  intakeWheels.spinFor(fwd, 1000, degrees, 80, vex::velocityUnits::pct);
}

void outtake() {
  // leftIntake.spinFor(rev, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
  // rightIntake.spinFor(rev, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
}

void score() {
  // botRoller.spinFor(fwd, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
  // topRoller.spinFor(fwd, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
}

void poop() {
  // botRoller.spinFor(fwd, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
  // topRoller.spinFor(rev, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
}

void descore() {
  
  // while (true) { // WOULD BE COOL IF WE GOT THIS TO WORK :(
  //   robotDrive.drive(fwd, 30, vex::velocityUnits::pct);
  //   if (frontRightWheel.efficiency()==0 && frontRightWheel.current()>0) {
  //     robotDrive.stop();
  //     break;
  //   }
  // }
  intake();
  robotDrive.driveFor(reverse, 10, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
}

int testMovement() { // just for testing
  task::sleep(2000);
  descore();
  this_thread::sleep_for(20000);
  // while (true) {
  //   float current_x, current_y, current_heading;
  //   link.get_local_location(current_x, current_y, current_heading);
  //   if (current_x != 0) {
  //     task::sleep(2000);
  //     goTo(0, 50, 0);
  //     task::sleep(10000);
  //   }
  //   this_thread::sleep_for(16);
  // }
  return 0;
}