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
    RF.spin(forward); RFv = 1;
    RB.spin(forward); RBv = 1;
    LF.spin(forward); LFv = 1;
    LB.spin(forward); LBv = 1;
    break;

    case 1: //FORWARD
    RF.spin(reverse); RFv = -1;
    RB.spin(reverse); RBv = -1;
    LF.spin(reverse); LFv = -1;
    LB.spin(reverse); LBv = -1;
    break;

    case 2: //CLOCKWISE
    RF.spin(forward); RFv = 1;
    RB.spin(forward); RBv = 1;
    LF.spin(reverse); LFv = -1;
    LB.spin(reverse); LBv = -1;
    
    break;

    case 3: //COUNTER CLOCKWISE
    RF.spin(reverse); RFv = -1;
    RB.spin(reverse); RBv = -1;
    LF.spin(forward); LFv = 1;
    LB.spin(forward); LBv = 1;
    break;

    case 4: //LEFT BACK
    RB.spin(forward); RBv = 1;
    LF.spin(forward); RFv = 1;
    break;

    case 5: //RIGHT FORWARD
    RB.spin(reverse); RBv = -1;
    LF.spin(reverse); LFv = -1;
    break;

    case 6: //LEFT FORWARD
    RF.spin(reverse); RFv = -1;
    LB.spin(reverse); LBv = -1;
    break;

    case 7: //RIGHT BACK
    RF.spin(forward); RFv = 1;
    LB.spin(forward); LBv = 1;
    break;

    case 8: //LEFT
    RF.spin(reverse); RFv = -1;
    RB.spin(forward); RBv = 1;
    LF.spin(forward); LFv = 1;
    LB.spin(reverse); LBv = -1;

    break;

    case 9: //RIGHT
    RF.spin(forward); RFv = 1;
    RB.spin(reverse); RBv = -1;
    LF.spin(reverse); LFv = -1;
    LB.spin(forward); LBv = 1;

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
    setSpeed(speed);
    RF.spinFor(forward, dist, degrees, false);  RFv = 1;
    RB.spinFor(forward, dist, degrees, false);  RBv = 1;
    LF.spinFor(forward, dist, degrees, false);  LFv = 1;
    LB.spinFor(forward, dist, degrees);         LBv = 1;
    break;

    case 1: //FORWARD
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);  RFv = -1;
    RB.spinFor(reverse, dist, degrees, false);  RBv = -1;
    LF.spinFor(reverse, dist, degrees, false);  LFv = -1;
    LB.spinFor(reverse, dist, degrees);         LBv = -1;
    break;

    case 2: //CLOCKWISE
    setSpeed(speed);
    RF.spinFor(forward, dist, degrees, false);  RFv = 1;
    RB.spinFor(forward, dist, degrees, false);  RBv = 1;
    LF.spinFor(reverse, dist, degrees, false);  LFv = -1;
    LB.spinFor(reverse, dist, degrees);         LBv = -1;
    break;

    case 3: //COUNTER CLOCKWISE
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);  RFv = -1;
    RB.spinFor(reverse, dist, degrees, false);  RBv = -1;
    LF.spinFor(forward, dist, degrees, false);  LFv = 1;
    LB.spinFor(forward, dist, degrees);         LBv = 1;
    break;

    case 4: //LEFT BACK
    setSpeed(speed);
    RB.spinFor(forward, dist, degrees, false);  RBv = 1;
    LF.spinFor(reverse, dist, degrees);         LFv = -1;
    break;

    case 5: //RIGHT FORWARD
    setSpeed(speed);
    RB.spinFor(reverse, dist, degrees, false);  RBv = -1;
    LF.spinFor(reverse, dist, degrees);         LFv = -1;
    break;
    
    case 6: //LEFT FORWARD
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false);  RFv = -1;
    LB.spinFor(reverse, dist, degrees);         LBv = -1;
    break;

    case 7: //RIGHT BACK
    setSpeed(speed);
    RF.spinFor(forward, dist, degrees, false);  RFv = 1;
    LB.spinFor(forward, dist, degrees);         LBv = 1;
    break;

    case 8: //LEFT
    setSpeed(speed);
    RF.spinFor(reverse, dist, degrees, false); RFv = -1;
    RB.spinFor(forward, dist, degrees, false); RBv = 1;
    LF.spinFor(forward,dist, degrees, false); LFv = 1;
    LB.spinFor(reverse, dist, degrees); LBv = -1;
    break;

    case 9: //RIGHT
    RF.spinFor(forward,dist, degrees, false); RFv = 1;
    RB.spinFor(reverse,dist, degrees, false); RBv = -1;
    LF.spinFor(reverse, dist, degrees, false); LFv = -1;
    LB.spinFor(forward, dist, degrees); LBv = 1;
    break;
  }
}