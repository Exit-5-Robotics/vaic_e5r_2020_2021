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
// Controller1          controller                    
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor8               motor         8               
// Motor9               motor         9               
// Motor16              motor         16              
// Motor17              motor         17              
// Motor18              motor         18              
// Motor19              motor         19              
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

void move(){
  Motor16.setVelocity(Controller1.Axis3.position(percent)/2, percent);
  Motor17.setVelocity(Controller1.Axis3.position(percent)/2, percent);
  Motor18.setVelocity(Controller1.Axis2.position(percent)/2, percent);
  Motor19.setVelocity(Controller1.Axis2.position(percent)/2, percent);

  Motor16.spin(forward);
  Motor17.spin(forward);
  Motor18.spin(forward);
  Motor19.spin(forward);

  Motor16.setStopping(hold);
  Motor17.setStopping(hold);
  Motor18.setStopping(hold);
  Motor19.setStopping(hold);
}

void indexer(){
  int speed = 400;
      Motor1.setVelocity(speed/2, rpm);
      Motor2.setVelocity(speed, rpm);
      //Motor3.setVelocity(speed, rpm);

  if (Controller1.ButtonX.pressing()){
    Motor1.spin(fwd);
    Motor2.spin(fwd);
  }
  else if (Controller1.ButtonR1.pressing()){
    Motor1.spin(fwd);
    Motor2.spin(reverse);
  }
  else if (Controller1.ButtonR2.pressing()){
    Motor1.spin(reverse);
    Motor2.spin(reverse);
  }
  else{
    Motor1.stop();
    Motor2.stop();
  }
}

void intake(){
  int speed = 600;
  Motor8.setVelocity(speed, rpm);
  Motor9.setVelocity(speed, rpm);

  if (Controller1.ButtonL1.pressing()){
    Motor8.spin(fwd);
    Motor9.spin(fwd);
  }

  else if (Controller1.ButtonL2.pressing()){
    Motor8.spin(reverse);
    Motor9.spin(reverse);
  }

  else{
    Motor8.stop();
    Motor9.stop();
  }
}

void xDrive(){

  Motor16.setVelocity(Controller1.Axis4.position()+Controller1.Axis1.position()-Controller1.Axis2.position(), percent);
  Motor17.setVelocity(Controller1.Axis4.position()-Controller1.Axis1.position()-Controller1.Axis2.position(), percent);
  Motor18.setVelocity(Controller1.Axis4.position()+Controller1.Axis1.position()+Controller1.Axis2.position(), percent);
  Motor19.setVelocity(Controller1.Axis4.position()-Controller1.Axis1.position()+Controller1.Axis2.position(), percent);

  Motor16.spin(forward);
  Motor17.spin(forward);
  Motor18.spin(forward);
  Motor19.spin(forward);
}

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
  //move();
  indexer();
  intake();
  xDrive();
  wait(100, msec);
  }
}
