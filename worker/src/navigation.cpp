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
  //direction settings: idk if this helps but here
  //0 = cw rotation
  //1 = ccw rotation
  //2 = forward
  //3 = backward
  //4 = left back
  //5 = right forward
  //6 = left forward
  //7 = right back

  //rotate cw
  if(direction1 == 0){
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(forward);
    LB.spin(forward);
  }

  //rotate ccw
  if(direction1 == 1){
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(reverse);
    LB.spin(reverse);
  }

  //drive forward
  if(direction1 == 2){
    RF.spin(forward);
    RB.spin(forward);
    LF.spin(reverse);
    LB.spin(reverse);
  }

  //drive backward
  if(direction1 == 3){
    RF.spin(reverse);
    RB.spin(reverse);
    LF.spin(forward);
    LB.spin(forward);
  }

  //double speed for these next ones

  //left back
  if(direction1 == 4){
    RB.spin(forward);
    LF.spin(reverse);
  }

  //right forward
  if(direction1 == 5){
    RB.spin(reverse);
    LF.spin(forward);
  }

  //left forward
  if(direction1 == 6){
    RF.spin(reverse);
    LB.spin(forward);
  }

  //right back
  if(direction1 == 7){
    RF.spin(forward);
    LB.spin(reverse);
  }
}