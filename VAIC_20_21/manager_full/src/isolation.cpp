#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  goTo(40, -48, 180);
  task::sleep(500);
  robotDrive.turnFor(left, 45, degrees, 30, velocityUnits::pct);
  thread intakeCornerFirst(intakeNoDrive);
  while(!goal.pressing()) robotDrive.drive(fwd, 80, velocityUnits::pct);
  robotDrive.stop();
  intakeCornerFirst.join();
  // score();
  // score();

  robotDrive.driveFor(reverse, 30, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(right, 45, degrees, 30, velocityUnits::pct);
  Brain.Screen.clearScreen();
  goTo(35, -7, 180);

  robotDrive.turnFor(right, 90, degrees, 30, velocityUnits::pct);
  
  if (testChange()) turnTo(270, 20);
  
  intakeWheels.spin(fwd, 100, velocityUnits::pct);
  thread intakeMid(intakeNoDrive);
  while (ballZero.value(analogUnits::mV) > 3300) robotDrive.drive(fwd, 40, velocityUnits::pct);
  robotDrive.stop();
  intakeMid.join();

  task::sleep(20000);
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
}