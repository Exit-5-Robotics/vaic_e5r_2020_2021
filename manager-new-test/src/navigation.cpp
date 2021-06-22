#include "vex.h"

using namespace vex;

void mainLoop(){

}

void blueInteraction(){
  thread sort(adjustWIntake);
  driveAutoDist(0, 150, 60);
  turnTo(90);
  driveAutoDist(1, 300, 50);
  toStartingPoint(8, 90);
  driveToTower(true);
  mainLoop();
}

void redInteraction(){
  thread sort(adjustWIntake);
  driveAutoDist(0, 150, 60);
  turnTo(90);
  driveAutoDist(1, 300, 50);
  toStartingPoint(9, 90);
  driveToTower(true);
  mainLoop();
}