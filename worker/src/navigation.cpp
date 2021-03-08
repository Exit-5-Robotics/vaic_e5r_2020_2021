//MOTOR 12 RIGHT FRONT
//MOTOR 14 RIGHT BACK
//MOTOR 18 LEFT FRONT
//MOTOR 13 LEFT BACK
#include "vex.h"

using namespace vex;

void driveAuto(int direction){
  //direction settings: idk if this helps but here
  //0 = cw rotation
  //1 = ccw rotation
  //2 = forward
  //3 = backward
  //4 = left back
  //5 = right forward
  //6 = left forward
  //7 = right back

  int speed = 100;

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

void driveControl(){

  RF.setVelocity(Controller1.Axis4.position(percent)+Controller1.Axis1.position(percent)-Controller1.Axis2.position(percent), percent);
  RB.setVelocity(Controller1.Axis4.position(percent)-Controller1.Axis1.position(percent)-Controller1.Axis2.position(percent), percent);
  LF.setVelocity(Controller1.Axis4.position(percent)+Controller1.Axis1.position(percent)+Controller1.Axis2.position(percent), percent);
  LB.setVelocity(Controller1.Axis4.position(percent)-Controller1.Axis1.position(percent)+Controller1.Axis2.position(percent), percent);

  RF.spin(forward);
  RB.spin(forward);
  LF.spin(forward);
  LB.spin(forward);
}

void intake(){
  int speed = 400;
  Motor8.setVelocity(speed, rpm);
  Motor9.setVelocity(speed, rpm);

  if(Controller1.ButtonR1.pressing()){
    Motor8.spin(forward);
    Motor9.spin(forward);
  }

  else if(Controller1.ButtonR2.pressing()){
    Motor8.spin(reverse);
    Motor9.spin(reverse);
  }

  else{
    Motor8.setStopping(hold);
    Motor9.setStopping(hold);

    Motor8.stop();
    Motor9.stop();
  }
}
 
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  
  
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
    driveControl();
    intake();
  }
}
