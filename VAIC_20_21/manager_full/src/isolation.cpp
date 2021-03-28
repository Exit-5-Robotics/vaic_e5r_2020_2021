#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  goTo(40, -48, 180);
  task::sleep(500);
  robotDrive.turnFor(left, 45, degrees, 30, velocityUnits::pct);
  intakeWheels.spin(fwd, 100, velocityUnits::pct);
  while(!goal.pressing()) robotDrive.drive(fwd, 80, velocityUnits::pct);
  robotDrive.stop();
  intakeWheels.spinFor(fwd, 500, degrees, 100, velocityUnits::pct);
  // score();
  // score();

  robotDrive.driveFor(reverse, 30, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(left, 45, degrees, 30, velocityUnits::pct);
  Brain.Screen.clearScreen();
  goTo(35, 7, 0);


  task::sleep(20000);
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
}