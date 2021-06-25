#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  
}

void keepDriving(){
  driveAutoDist(1, 110, 60);
}

void intakeMore(){
 intakeWheels.setVelocity(100, pct);
 intakeWheels.spinFor(fwd, 1, seconds); 
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
  //get to line
  //driveToLine(1, 30, 1400, 'R');
  driveAutoDist(7, 600, 70);
  turnTo(242);
  //scores it
  driveToTower(false);
  //get back to the line asshole
  driveToLine(0, 30, 2000, 'R');
  thread adjusting(adjustHold);
  turnTo(42);
  thread pushBack(intakeMore);
  driveAutoDist(1, 1400, 60);
  //scoring middle tower
  thread driveMore(keepDriving);
  scoringRollers.setVelocity(100, percentUnits::pct);
  scoringRollers.spin(fwd);
  while(ballZero.value(pct) > 64){}
  scoringRollers.stop();
  topRoller.spinFor(fwd, 0.8, seconds);
  //going to third tower
  driveAutoDist(0, 230, 60);
  this_thread::sleep_for(500);
  thread adjustingMorey(adjustWIntake);
  turnTo(90);
  this_thread::sleep_for(500);
  driveAutoDist(9, 800, 70);
  driveToLine(9, 10, 7000, 'L');
  turnTo(91);
  this_thread::sleep_for(500);
  driveAutoDist(1, 475, 30);
  driveToLine(1, 5, 6000, 'R');
  driveAutoDist(1, 100, 30);
  this_thread::sleep_for(500);
  driveAutoDist(8, 150, 20);
  turnTo(180);
  this_thread::sleep_for(500);
  driveToTower(false);
  driveAutoDist(0, 30, 500);
}