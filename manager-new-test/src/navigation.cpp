#include "vex.h"

using namespace vex;

void mainLoop(){
  //get to starting point
  driveAutoDist(0, 500, 70);
  //the loop commenses
  int iteration = 1;
  while(true){
    driveAutoDist(8, 800, 70);
    turnTo(iteration*90);
    driveAutoDist(8, 800, 70);
    iteration--;
    if(iteration == -1){
      iteration = 3;
    }
  }
}



/*
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
*/