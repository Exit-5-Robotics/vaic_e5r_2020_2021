#include "vex.h"

using namespace vex;

void fixArms(){
  intakeArms.setVelocity(50, pct);
  intakeArms.spin(fwd);
}

void adjustLines(int dir){
  driveAutoDist(dir, 10, 20);
}

void justInCase(){
  this_thread::sleep_for(4000);
  intakeArms.stop();
  intakeArms.setVelocity(90, pct);
  bothRollers.setVelocity(100, pct);
  intakeArms.spin(forward);
  storer.spin(fwd);
  bothRollers.spin(forward);
  wait(2.5, seconds);
  intakeArms.stop();
  bothRollers.stop();
  storer.stop();
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
  while(rightLine.value(percentUnits::pct) > 40){}
  pause();
  adjustLines(1); // adjusting for wrong line placemement lol
  turnTo(140);
  driveToTower();
  //scoring first tower
  poopEverything();
  score();
  //go to second tower
  intakeArms.spin(reverse);
  driveAutoDist(0, 200, 30);
  thread makeSure(justInCase);
  driveAuto(0); setSpeed(10);
  //thread resetArms(fixArms);
  while(rightLine.value(percentUnits::pct) > 40){}
  pause();
  adjustLines(0);
  turnTo(90);
  driveAutoDist(8, 540, 30);
  turnTo(90);
  driveAutoDist(8, 540, 30);
  turnTo(50);
  //scoring second tower
  driveToTower();
  scoreTower(2);
  driveAutoDist(0, 600, 90);
}