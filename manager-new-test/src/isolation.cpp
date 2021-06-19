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
  driveToTower();
  //get back to the line asshole
  driveToLine(0, 40, 900, 'R');
  turnTo(264);
  toStartingPoint(8, 270);
  turnTo(267);
  driveToLine(1, 40, 3000, 'L');
  driveAutoDist(0, 100, 20);
  //score new tower
  driveAutoDist(9, 200, 30);
  turnTo(177);
  driveToTower();
  tilt.resetHeading();
  //go to ending position to await interaction period
  driveAutoDist(0, 200, 50);
  driveAutoDist(8, 1200, 80);
  turnTo(270);

}