#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  
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
  turnTo(44);
  thread adjusting(adjustHold);
  driveAutoDist(1, 1500, 60);
  //scoring middle tower
  scoringRollers.setVelocity(100, percentUnits::pct);
  scoringRollers.spin(fwd);
  while(ballZero.value(pct) > 64){}
  scoringRollers.stop();
  topRoller.spinFor(fwd, 0.8, seconds);
  //going to third tower
  thread adjustingMorey(adjustHold);
  driveAutoDist(0, 200, 60);
  this_thread::sleep_for(500);
  turnTo(90);
  this_thread::sleep_for(500);
  driveAutoDist(9, 800, 70);
  driveToLine(9, 10, 7000, 'L');
  turnTo(91);
  this_thread::sleep_for(500);
  driveAutoDist(1, 475, 30);
  driveToLine(1, 5, 5000, 'R');
  driveAutoDist(1, 100, 30);
  this_thread::sleep_for(500);
  driveAutoDist(8, 100, 30);
  turnTo(180);
  this_thread::sleep_for(500);
  driveToTower(false);
}