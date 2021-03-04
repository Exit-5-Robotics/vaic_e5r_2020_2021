/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RF                   motor         12              
// RB                   motor         14              
// LF                   motor         18              
// LB                   motor         13              
// Controller1          controller                    
// Motor8               motor         8               
// Motor9               motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//MOTOR 12 RIGHT FRONT
//MOTOR 14 RIGHT BACK
//MOTOR 18 LEFT FRONT
//MOTOR 13 LEFT BACK

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
