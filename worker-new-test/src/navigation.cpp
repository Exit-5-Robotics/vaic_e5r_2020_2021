#include "vex.h"

using namespace vex;

int currentTower = 0; //current tower we fixing
bool ballNeeded; // do we need another ball to fix a tower?
bool haveAnotherBall; //if we are currently storing an additional ball of out color

void mainLoop(){
  turnTo(91);
  driveAutoDist(9, 200, 80);
  while(true){
    //going to the left
    driveAutoDist(8, 2800, 60);
    //making it look like this isnt a sabatoge ;)
    turnTo(45);
    intakeArms.spinFor(fwd, 1000, msec);
    turnTo(90);

    //going to the right
    driveAutoDist(8, 2800, 90);
    //making it look like this isnt a sabatoge ;)
    turnTo(135);
    intakeArms.spinFor(fwd, 1000, msec);
    turnTo(90);
  }
}