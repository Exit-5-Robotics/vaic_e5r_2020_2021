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
// IntakeL              motor         1               
// LF                   motor         2               
// Index1               motor         11              
// Index2               motor         12              
// LB                   motor         16              
// RB                   motor         17              
// RF                   motor         18              
// IntakeR              motor         19              
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
  //mecanum
  LF.setVelocity(Controller1.Axis2.position()+Controller1.Axis1.position()+Controller1.Axis4.position(), percent);
  LB.setVelocity(Controller1.Axis2.position()-Controller1.Axis1.position()+Controller1.Axis4.position(), percent);
  RF.setVelocity(Controller1.Axis2.position()-Controller1.Axis1.position()-Controller1.Axis4.position(), percent);
  RB.setVelocity(Controller1.Axis2.position()+Controller1.Axis1.position()-Controller1.Axis4.position(), percent);

  LF.spin(forward);
  LB.spin(forward);
  RF.spin(forward);
  RB.spin(forward);
  
  Brain.Screen.printAt(10, 30, "LF: %f", LF.velocity(rpm));
  Brain.Screen.printAt(10, 50, "LB: %f", LB.velocity(rpm));
  Brain.Screen.printAt(150, 30, "RF: %f", RF.velocity(rpm));
  Brain.Screen.printAt(150, 50, "RB: %f", RB.velocity(rpm));

}

void indexer(){
  int speed = 400;
      Index1.setVelocity(speed/2, rpm);
      Index2.setVelocity(speed, rpm);

  if (Controller1.ButtonR1.pressing()){
    Index1.spin(fwd);
    Index2.spin(reverse);
  }
  else if (Controller1.ButtonR2.pressing()){
    Index1.spin(reverse);
    Index2.spin(reverse);
  }
  else{
    Index1.stop();
    Index2.stop();
  }
}

void intake(){
  int speed = 600;
  IntakeL.setVelocity(speed, rpm);
  IntakeR.setVelocity(speed, rpm);

  if (Controller1.ButtonL1.pressing()){
    IntakeL.spin(fwd);
    IntakeR.spin(fwd);
  }

  else if (Controller1.ButtonL2.pressing()){
    IntakeL.spin(reverse);
    IntakeR.spin(reverse);
  }

  else{
    IntakeL.stop();
    IntakeR.stop();
  }
}

/*void xDrive(){

  Motor16.setVelocity(Controller1.Axis4.position()+Controller1.Axis1.position()-Controller1.Axis2.position(), percent);
  Motor17.setVelocity(Controller1.Axis4.position()-Controller1.Axis1.position()-Controller1.Axis2.position(), percent);
  Motor18.setVelocity(Controller1.Axis4.position()+Controller1.Axis1.position()+Controller1.Axis2.position(), percent);
  Motor19.setVelocity(Controller1.Axis4.position()-Controller1.Axis1.position()+Controller1.Axis2.position(), percent);

  Motor16.spin(forward);
  Motor17.spin(forward);
  Motor18.spin(forward);
  Motor19.spin(forward);
}*/

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
  indexer();
  intake();
  //xDrive();
  move();
    wait(100, msec);
  }
}
