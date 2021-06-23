#include "vex.h"

using namespace vex;

void fixArms(){
  intakeArms.setVelocity(50, pct);
  intakeArms.spinFor(fwd, 1, seconds);
}

void blueIsolation(){
  //setup
  shelf.setVelocity(20, pct);
  shelf.spinFor(fwd, 0.3, seconds);
  shelf.stop(hold);
  //go to first tower
  driveAutoDist(1, 250, 20);
  driveAuto(1); setSpeed(10);
  while(fabs(rightLine.value(percentUnits::pct) - getLineColorR()) > 10){}
  pause();
  turnTo(125);
  driveToTower();
  //scoring first tower
  poopEverything();
  score();
  //go to second tower
  intakeArms.spin(reverse);
  driveAutoDist(0, 150, 30);
  intakeArms.stop();
  driveAuto(0); setSpeed(10);
  while(fabs(rightLine.value(percentUnits::pct) - getLineColorR()) > 10){}
  pause();
  turnTo(90);
  driveAutoDist(8, 550, 30);
  turnTo(90);
  driveAutoDist(8, 550, 30);
  turnTo(53);
  //scoring second tower
  driveToTower();
  scoreTower(2);
}