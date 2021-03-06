#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  // // goTo( 30, -30, 135);
  robotDrive.driveFor(fwd, 28, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(left, 80, degrees, 30, velocityUnits::pct);
  turnTo(135, 20);
  // // intake(20);
  intakeWheels.spin(fwd, 100, velocityUnits::pct);
  robotDrive.driveFor(fwd, 20, inches, 30, velocityUnits::pct);
  robotDrive.driveFor(fwd, 10, inches, 20, velocityUnits::pct);
  intakeWheels.spinFor(fwd, 360, degrees, 60, velocityUnits::pct, false);
  adjustHold();
  while(!goal.pressing()) robotDrive.drive(fwd, 20, velocityUnits::pct);
  score();
  score();

  // robotDrive.driveFor(reverse, 45, inches, 30, velocityUnits::pct);


  // intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  // robotDrive.driveFor(fwd, 20, inches, 30, velocityUnits::pct);
  // robotDrive.driveFor(fwd, 20, inches, 20, velocityUnits::pct);
  // intakeWheels.spinFor(fwd, 360, degrees, 50, velocityUnits::pct, false);
  // // robotDrive.driveFor(reverse, 15, inches, 30, velocityUnits::pct);
  task::sleep(20000);
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
}