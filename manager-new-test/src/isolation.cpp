#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
  //get to line
  //driveToLine(1, 30, 1400, 'R');
  driveAutoDist(4, 600, 70);
  turnTo(125);
  //scores it
  driveToTower(false);
  //get back to the line asshole
  driveToLine(0, 40, 900, 'R');
  turnTo(322);
  driveAutoDist(1, 1500, 80);
  //scoring middle tower
  scoringRollers.setVelocity(100, percentUnits::pct);
  scoringRollers.spin(fwd);
  while(ballZero.value(pct) > 64){}
  scoringRollers.stop();
  topRoller.spinFor(fwd, 0.8, seconds);
}