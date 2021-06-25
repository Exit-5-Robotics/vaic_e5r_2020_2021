#include "vex.h"

using namespace vex;

void fixArms(){
  intakeArms.setVelocity(50, pct);
  intakeArms.spinFor(fwd, 2, seconds);
}

void blueIsolation(){
  //setup
  shelf.setVelocity(20, pct);
  shelf.spinFor(fwd, 0.3, seconds);
  shelf.stop(hold);
  //go to first tower
  thread armSetup(fixArms);
  driveAutoDist(1, 300, 30);
  driveAuto(5); setSpeed(10);
  while(fabs(rightLine.value(percentUnits::pct) - getLineColorR()) > 10){}
  pause();
  turnTo(140);
  driveToTower();
  //scoring first tower
  poopEverything();
  score();
  //go to second tower
  intakeArms.spin(reverse);
  driveAutoDist(0, 200, 30);
  intakeArms.stop();
  driveAuto(0); setSpeed(10);
  thread resetArms(fixArms);
  while(fabs(rightLine.value(percentUnits::pct) - getLineColorR()) > 10){}
  pause();
  turnTo(90);
  driveAutoDist(8, 540, 30);
  turnTo(90);
  driveAutoDist(8, 540, 30);
  turnTo(47);
  //scoring second tower
  driveToTower();
  scoreTower(2);
  driveAutoDist(0, 200, 90);
}