// RF    - PORT 12
// RB    - PORT 14
// LF    - PORT 18
// LB    - PORT 13
// Intake - PORT 9
// Roller - PORT 8

#include "vex.h"

using namespace vex;

void setSpeed(int speed){
  RF.setVelocity(speed, rpm);
  RB.setVelocity(speed, rpm);
  LF.setVelocity(speed, rpm);
  LB.setVelocity(speed, rpm);
}

void driveAuto(int direction1){
  //DIRECTION SETTINGS
  //0 = FORWARD
  //1 = BACKWARD
  //2 = CLOCKWISE
  //3 = COUNTER CLOCKWISE
  //4 = LEFT BACK
  //5 = RIGHT FORWARD
  //6 = LEFT FORWARD
  //7 = RIGHT BACK

  switch(direction1){
    case 0: //FORWARD
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(reverse);
    LB.spin(reverse);
    break;

    case 1: //BACKWARD
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(forward);
    LB.spin(forward);
    break;

    case 2: //CLOCKWISE
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(forward);
    LB.spin(forward);
    
    break;

    case 3: //COUNTER CLOCKWISE
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(reverse);
    LB.spin(reverse);
    break;

    case 4: //LEFT BACK
    RB.spin(forward);
    LF.spin(reverse);
    break;

    case 5: //RIGHT FORWARD
    RB.spin(reverse);
    LF.spin(forward);
    break;

    case 6: //LEFT FORWARD
    RF.spin(reverse);
    LB.spin(forward);
    break;

    case 7: //RIGHT BACK
    RF.spin(forward);
    LB.spin(reverse);
    break;

  }
}

//DRIVE FOR DIRECTION AND DISTANCE
void driveAutoDist(int direction1, int dist){ 
  //DIRECTION SETTINGS
  //0 = FORWARD
  //1 = BACKWARD
  //2 = CLOCKWISE
  //3 = COUNTER CLOCKWISE
  //4 = LEFT BACK
  //5 = RIGHT FORWARD
  //6 = LEFT FORWARD
  //7 = RIGHT BACK
  switch (direction1) {
    case 0: //FORWARD
    RF.spinFor(forward, dist, degrees, false);
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(reverse, dist, degrees, false);
    LB.spinFor(reverse, dist, degrees);
    break;

    case 1: //BACKWARD
    RF.spinFor(reverse, dist, degrees, false);
    RB.spinFor(reverse, dist, degrees, false);
    LF.spinFor(forward, dist, degrees, false);
    LB.spinFor(forward, dist, degrees);
    break;

    case 2: //CLOCKWISE
    RF.spinFor(forward, dist, degrees, false);
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(forward, dist, degrees, false);
    LB.spinFor(forward, dist, degrees);
    break;

    case 3: //COUNTER CLOCKWISE
    RF.spinFor(reverse, dist, degrees, false);
    RB.spinFor(reverse, dist, degrees, false);
    LF.spinFor(reverse, dist, degrees, false);
    LB.spinFor(reverse, dist, degrees);
    break;

    case 4: //LEFT BACK
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(forward, dist, degrees);
    break;

    case 5: //RIGHT FORWARD
    RB.spinFor(reverse, dist, degrees, false);
    LF.spinFor(forward, dist, degrees);
    break;
    
    case 6: //LEFT FORWARD
    RF.spinFor(reverse, dist, degrees, false);
    LB.spinFor(forward, dist, degrees);
    break;

    case 7: //RIGHT BACK
    RF.spinFor(forward, dist, degrees, false);
    LB.spinFor(reverse, dist, degrees);
    break;
    }
}