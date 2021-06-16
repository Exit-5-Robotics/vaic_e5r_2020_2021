#include "vex.h"

using namespace vex;

void redIsolation() {
  /* (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits */
  
}

void blueIsolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
  //get to line
  driveToLine(1, 30, 1600, 'R');
  turnTo(115);
  //scores it
  driveToTower();
  //get back to the line asshole
  driveToLine(0, 40, 1100, 'R');
  turnTo(270);
  toStartingPoint(8, 270);
  driveToLine(1, 40, 2000, 'L');
}