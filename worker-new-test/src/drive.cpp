// RF    - PORT 12
// RB    - PORT 14
// LF    - PORT 18
// LB    - PORT 13
// Intake - PORT 9
// Roller - PORT 8

#include "vex.h"

using namespace vex;

int RFv;
int RBv;
int LFv;
int LBv;

void setSpeed(int speed){
  RF.setVelocity(RFv * speed, pct);
  RB.setVelocity(RBv * speed, pct);
  LF.setVelocity(LFv * speed, pct);
  LB.setVelocity(LBv * speed, pct);
}

void driveAuto(int direction1){
  //DIRECTION SETTINGS
  //0 = BACKWARD
  //1 = FORWARD
  //2 = CLOCKWISE (right)
  //3 = COUNTER CLOCKWISE (left)
  //4 = LEFT BACK
  //5 = RIGHT FORWARD
  //6 = LEFT FORWARD
  //7 = RIGHT BACK
  //8 = LEFT
  //9 = RIGHT

  switch(direction1){
    case 0: //BACKWARD
    RFv = 1; RBv = 1; LFv = 1; LBv = 1;
    RF.spin(forward); 
    RB.spin(forward); 
    LF.spin(forward); 
    LB.spin(forward);
    break;

    case 1: //FORWARD
    RFv = -1; RBv = -1; LFv = -1; LBv = -1;
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(reverse);
    LB.spin(reverse);
    break;

    case 2: //CLOCKWISE
    RFv = 1; RBv = 1; LFv = -1; LBv = -1;
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(reverse);
    LB.spin(reverse);
    
    break;

    case 3: //COUNTER CLOCKWISE
    RFv = -1; RBv = -1; LFv = 1; LBv = 1;
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(forward);
    LB.spin(forward);
    break;

    case 4: //LEFT BACK
    RBv = 1; LFv = 1;
    RB.spin(forward);
    LF.spin(forward);
    break;

    case 5: //RIGHT FORWARD
    RBv = -1; LFv = -1;
    RB.spin(reverse); RBv = -1;
    LF.spin(reverse); LFv = -1;
    break;

    case 6: //LEFT FORWARD
    RFv = -1; LBv = -1;
    RF.spin(reverse); RFv = -1;
    LB.spin(reverse); LBv = -1;
    break;

    case 7: //RIGHT BACK
    RFv = 1; LBv = 1;
    RF.spin(forward); RFv = 1;
    LB.spin(forward); LBv = 1;
    break;

    case 8: //LEFT
    RFv = -1; RBv = 1; LFv = 1; LBv = -1;
    RF.spin(reverse);
    RB.spin(forward);
    LF.spin(forward);
    LB.spin(reverse);

    break;

    case 9: //RIGHT
    RFv = 1; RBv = -1; LFv = -1; LBv = 1;
    RF.spin(forward);
    RB.spin(reverse);
    LF.spin(reverse);
    LB.spin(forward);

    break;
  }
}

//STOP ALL WHEELS
void pause(){
  RF.stop();
  LF.stop();
  RB.stop();
  LB.stop();
}

//DRIVE FOR DIRECTION AND DISTANCE
void driveAutoDist(int direction1, int dist, int speed){ 
  //DIRECTION SETTINGS
  //0 = BACKWARD
  //1 = FORWARD
  //2 = CLOCKWISE
  //3 = COUNTER CLOCKWISE
  //4 = LEFT BACK
  //5 = RIGHT FORWARD
  //6 = LEFT FORWARD
  //7 = RIGHT BACK
  switch (direction1) {
    case 0: //BACKWARD
    RFv = 1; RBv = 1; LFv = 1; LBv = 1;
    setSpeed(speed);
    RF.spinFor(forward, dist, degrees, false);
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(forward, dist, degrees, false);
    LB.spinFor(forward, dist, degrees);
    break;

    case 1: //FORWARD
    RFv = -1; RBv = -1; LFv = -1; LBv = -1;
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);
    RB.spinFor(reverse, dist, degrees, false);
    LF.spinFor(reverse, dist, degrees, false);
    LB.spinFor(reverse, dist, degrees);
    break;

    case 2: //CLOCKWISE
    RFv = 1; RBv = 1; LFv = -1; LBv = -1;
    setSpeed(speed);
    RF.spinFor(forward, dist, degrees, false);
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(reverse, dist, degrees, false);
    LB.spinFor(reverse, dist, degrees);
    break;

    case 3: //COUNTER CLOCKWISE
    RFv = -1; RBv = -1; LFv = 1; LBv = 1;
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);
    RB.spinFor(reverse, dist, degrees, false);
    LF.spinFor(forward, dist, degrees, false);
    LB.spinFor(forward, dist, degrees);
    break;

    case 4: //LEFT BACK
    RBv = 1; LFv = -1;
    setSpeed(speed);
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(forward, dist, degrees);
    break;

    case 5: //RIGHT FORWARD
    RBv = -1; LFv = -1;
    setSpeed(speed);
    RB.spinFor(reverse, dist, degrees, false);  RBv = -1;
    LF.spinFor(reverse, dist, degrees);         LFv = -1;
    break;
    
    case 6: //LEFT FORWARD
    RFv = -1; LBv = -1;
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);  RFv = -1;
    LB.spinFor(reverse, dist, degrees);         LBv = -1;
    break;

    case 7: //RIGHT BACK
    RFv = 1; LBv = 1;
    setSpeed(speed);
    RF.spinFor(forward, dist, degrees, false);  RFv = 1;
    LB.spinFor(forward, dist, degrees);         LBv = 1;
    break;

    case 8: //LEFT
    RFv = -1; RBv = 1; LFv = 1; LBv = -1;
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);
    RB.spinFor(forward, dist, degrees, false);
    LF.spinFor(forward, dist, degrees, false);
    LB.spinFor(reverse, dist, degrees);
    break;

    case 9: //RIGHT
    RFv = 1; RBv = -1; LFv = -1; LBv = 1;
    RF.spinFor(forward, dist, degrees, false);
    RB.spinFor(reverse, dist, degrees, false);
    LF.spinFor(reverse, dist, degrees, false);
    LB.spinFor(forward, dist, degrees);
    break;
  }
}