#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  driveAngleFor(10, 90, 50);
  goToX(-40, 48, 180);
  goToY(-40, 48, 180);
  task::sleep(500);
  robotDrive.turnFor(left, 45, degrees, 30, velocityUnits::pct);
  thread intakeCornerFirst(intakeNoDrive);
  while(!goal.pressing()) robotDrive.drive(fwd, 50, velocityUnits::pct);
  robotDrive.stop();
  intakeCornerFirst.join();
  robotDrive.driveFor(reverse, 5, inches, 30, velocityUnits::pct);
  intakeWheels.spinFor(1000, degrees, 100, velocityUnits::pct);
  robotDrive.driveFor(fwd, 5, inches, 30, velocityUnits::pct);
  adjustHold();
  score();

  LinkA.send("First");

  robotDrive.driveFor(reverse, 30, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(right, 45, degrees, 30, velocityUnits::pct);
  goToX(-35, 7, 180);
  goToY(-35, 7, 180);

  robotDrive.turnFor(right, 90, degrees, 30, velocityUnits::pct);
  if (testChange()) turnTo(90, 20);
  
  intakeWheels.spin(fwd, 100, velocityUnits::pct);
  thread intakeMid(intakeNoDrive);
  robotDrive.drive(fwd, 30, velocityUnits::pct);

  while (ballThree.value(analogUnits::mV) > 3300 && local_x > 5);
  robotDrive.stop();
  intakeMid.join();

  intakeWheels.spinFor(1500, degrees, 100, velocityUnits::pct, false);
  thread moveMid(adjustHold);
  robotDrive.driveFor(reverse, 10, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(left, 40, deg, 40, velocityUnits::pct);
  turnTo(0, 20);
  robotDrive.turnFor(left, 90, deg, 30, velocityUnits::pct);
  if (testChange()) turnTo(90, 20);
  moveMid.join();

  thread intakeMidSide(intakeNoDrive);
  while(!goal.pressing()) robotDrive.drive(fwd, 50, velocityUnits::pct);
  robotDrive.stop();
  intakeMidSide.join();
  intakeWheels.spinFor(1000, degrees, 100, velocityUnits::pct);
  score();
  
  LinkA.send("Second");

  task::sleep(250);
  adjustHold();
  score();

  // rollers keep spinning for some reason
  robotDrive.driveFor(reverse, 10, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(left, 30, degrees, 50, velocityUnits::pct);
  // goTo(40, 48, 0);

  // robotDrive.turnFor(right, 45, degrees, 20, velocityUnits::pct);

  // thread intakeCornerLast(intakeNoDrive);
  // while(!goal.pressing()) robotDrive.drive(fwd, 80, velocityUnits::pct);
  // robotDrive.stop();
  // intakeCornerLast.join();
  // intakeWheels.spinFor(1000, degrees, 100, velocityUnits::pct);
  // adjustHold();
  // score();

  task::sleep(20000);
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
  driveAngleFor(10, 90, 50);
  goToX(40, -48, 180);
  goToY(40, -48, 180);
  task::sleep(500);
  robotDrive.turnFor(left, 45, degrees, 30, velocityUnits::pct);
  thread intakeCornerFirst(intakeNoDrive);
  while(!goal.pressing()) robotDrive.drive(fwd, 50, velocityUnits::pct);
  robotDrive.stop();
  intakeCornerFirst.join();
  robotDrive.driveFor(reverse, 5, inches, 30, velocityUnits::pct);
  intakeWheels.spinFor(1000, degrees, 100, velocityUnits::pct);
  robotDrive.driveFor(fwd, 5, inches, 30, velocityUnits::pct);
  adjustHold();
  score();

  LinkA.send("First");

  robotDrive.driveFor(reverse, 30, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(right, 45, degrees, 30, velocityUnits::pct);
  goToX(35, -7, 180);
  goToY(35, -7, 180);

  robotDrive.turnFor(right, 90, degrees, 30, velocityUnits::pct);
  if (testChange()) turnTo(270, 20);
  
  intakeWheels.spin(fwd, 100, velocityUnits::pct);
  thread intakeMid(intakeNoDrive);
  robotDrive.drive(fwd, 30, velocityUnits::pct);

  while (ballThree.value(analogUnits::mV) > 3300 && local_x < -5);
  robotDrive.stop();
  intakeMid.join();

  intakeWheels.spinFor(1500, degrees, 100, velocityUnits::pct, false);
  thread moveMid(adjustHold);
  robotDrive.driveFor(reverse, 10, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(left, 40, deg, 40, velocityUnits::pct);
  turnTo(180, 20);
  robotDrive.turnFor(left, 90, deg, 30, velocityUnits::pct);
  if (testChange()) turnTo(270, 20);
  moveMid.join();

  thread intakeMidSide(intakeNoDrive);
  while(!goal.pressing()) robotDrive.drive(fwd, 50, velocityUnits::pct);
  robotDrive.stop();
  intakeMidSide.join();
  intakeWheels.spinFor(1000, degrees, 100, velocityUnits::pct);
  score();
  
  LinkA.send("Second");

  task::sleep(250);
  adjustHold();
  score();

  // rollers keep spinning for some reason
  robotDrive.driveFor(reverse, 10, inches, 30, velocityUnits::pct);
  robotDrive.turnFor(left, 30, degrees, 50, velocityUnits::pct);
  // goTo(-40, -48, 0);

  // robotDrive.turnFor(right, 45, degrees, 20, velocityUnits::pct);

  // thread intakeCornerLast(intakeNoDrive);
  // while(!goal.pressing()) robotDrive.drive(fwd, 80, velocityUnits::pct);
  // robotDrive.stop();
  // intakeCornerLast.join();
  // intakeWheels.spinFor(1000, degrees, 100, velocityUnits::pct);
  // adjustHold();
  // score();

  task::sleep(20000);
}