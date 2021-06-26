#include "vex.h"

using namespace vex;


void mainLoop(){ // looping in a line across the field line
  //getting into position
  driveAutoDist(0, 500, 30);
  turnTo(180);
  driveAutoDist(9, 500, 50);
  turnTo(270);
  while(true){
    //going to the right
    driveAutoDist(9, 2500, 60);
    //making it look like this isnt a sabatoge ;)
    turnTo(315);
    intakeWheels.spinFor(fwd, 1000, msec);
    turnTo(270);

    //going to the left
    driveAutoDist(8, 2500, 60);
    //making it look like this isnt a sabatoge ;)
    turnTo(225);
    intakeWheels.spinFor(fwd, 1000, msec);
    turnTo(270);
  }
}

/*
void mainLoop(){ // circling around the field
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
*/


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