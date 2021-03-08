// RF    - PORT 12
// RB    - PORT 14
// LF    - PORT 18
// LB    - PORT 13
// Intake - PORT 9
// Roller - PORT 8

#include "vex.h"

using namespace vex;

void driveAuto(int direction, int speed){
  //direction settings: idk if this helps but here
  //0 = cw rotation
  //1 = ccw rotation
  //2 = forward
  //3 = backward
  //4 = left back
  //5 = right forward
  //6 = left forward
  //7 = right back

  RF.setVelocity(speed, rpm);
  RB.setVelocity(speed, rpm);
  LF.setVelocity(speed, rpm);
  LB.setVelocity(speed, rpm);
  

  //rotate cw
  if(direction == 0){
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(forward);
    LB.spin(forward);
  }

  //rotate ccw
  if(direction == 1){
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(reverse);
    LB.spin(reverse);
  }

  //drive forward
  if(direction == 2){
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(reverse);
    LB.spin(reverse);
  }

  //drive backward
  if(direction == 3){
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(forward);
    LB.spin(forward);
  }

  speed*=2;

  //left back
  if(direction == 4){
    RB.spin(forward);
    LF.spin(reverse);
  }

  //right forward
  if(direction == 5){
    RB.spin(reverse);
    LF.spin(forward);
  }

  //left forward
  if(direction == 6){
    RF.spin(reverse);
    LB.spin(forward);
  }

  //right back
  if(direction == 7){
    RF.spin(forward);
    LB.spin(reverse);
  }
}