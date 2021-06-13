#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Tilter = motor(PORT11, ratio36_1, false);
controller Controller1 = controller(primary);

motor IntakeL = motor(PORT9, ratio18_1, false);
motor IntakeR = motor(PORT8, ratio18_1, true);
motor botRoller = motor(PORT1, ratio18_1, false);
motor topRoller = motor(PORT2, ratio18_1, false);
motor backLeftWheel = motor(PORT16, ratio18_1, false);
motor frontLeftWheel = motor(PORT17, ratio18_1, false);
motor backRightWheel = motor(PORT18, ratio18_1, true);
motor frontRightWheel = motor(PORT19, ratio18_1, true);
line ball = line(Brain.ThreeWirePort.C);
distance detec = distance(PORT20);

motor_group   LeftDrive( backLeftWheel, frontLeftWheel );
motor_group   RightDrive( backRightWheel, frontRightWheel );


// VEXcode generated functions
// define variables used for controlling drive based on controller inputs
bool DrivetrainNeedsToBeStopped_Controller1 = true;
bool DrivetrainHNeedsToBeStopped_Controller1 = true;
bool turnyturnNeedsToBeStopped_Controller1 = true;
bool DriveSpeed = true;
bool IntakeNeedsStop = true;
bool TilterNeedsStop = true;
bool ArmsNeedStop = true;

void drivingSpeed() {
  ::DriveSpeed = ::DriveSpeed?false:true;
}

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // calculate the drivetrain motor velocities from the controller joystick axes
    // movement = Axis3, perspective = Axis2
    int drivetrainForwardBackward = Controller1.Axis3.position();
    int drivetrainPerspective = Controller1.Axis1.position();
    // check if the value is inside of the deadband range
    if (drivetrainForwardBackward < 5 && drivetrainForwardBackward > -5) { //////////
      // check if the motor has already been stopped
      if (DrivetrainNeedsToBeStopped_Controller1) {
        LeftDrive.stop(vex::brakeType::brake);
        RightDrive.stop(vex::brakeType::brake);
        // tell the code that the motors been stopped
        DrivetrainNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop motor next time input is in the deadband range
      DrivetrainNeedsToBeStopped_Controller1 = true;
    }
    
    // toggle drivespeed
    Controller1.ButtonA.released(drivingSpeed);

    // only tell the motor to spin if the values are not in the deadband range
    if (DrivetrainNeedsToBeStopped_Controller1) {
      if (DriveSpeed) {
        if (drivetrainForwardBackward <= 70 || drivetrainForwardBackward <= -70) {
          LeftDrive.setVelocity(pow(drivetrainForwardBackward, 2) / 1.2*drivetrainForwardBackward, percent);
          RightDrive.setVelocity(pow(drivetrainForwardBackward, 2) / 1.2*drivetrainForwardBackward, percent);
        }
        LeftDrive.setVelocity(drivetrainForwardBackward, percent);
        RightDrive.setVelocity(drivetrainForwardBackward, percent);
      } else {
        LeftDrive.setVelocity(drivetrainForwardBackward/5, percent);
        RightDrive.setVelocity(drivetrainForwardBackward/5, percent);
      }
      LeftDrive.spin(forward);
      RightDrive.spin(forward);
    }
    // deadband?? yeenaw
    if (drivetrainPerspective < 5 && drivetrainPerspective > -5) {
      if (turnyturnNeedsToBeStopped_Controller1) {
        LeftDrive.stop(vex::brakeType::brake);
        RightDrive.stop(vex::brakeType::brake);
        // tell the code that the motors been stopped
        turnyturnNeedsToBeStopped_Controller1 = false;
      }
    } else {
      turnyturnNeedsToBeStopped_Controller1 = true;
    }
    if (turnyturnNeedsToBeStopped_Controller1) {
      if (DriveSpeed) {
        LeftDrive.setVelocity(drivetrainPerspective, pct);
        RightDrive.setVelocity(drivetrainPerspective, pct);
      } else {
        LeftDrive.setVelocity(drivetrainPerspective/5, pct);
        RightDrive.setVelocity(drivetrainPerspective/5, pct);
      }
      LeftDrive.spin(forward);
      RightDrive.spin(reverse);
    }
    // Up/Down buttons control Arms
    if (Controller1.ButtonL1.pressing()) {
      IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      TilterNeedsStop = false;
    } else if (Controller1.ButtonL2.pressing()) {
      IntakeL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      TilterNeedsStop = false;
    } else if (!TilterNeedsStop) {
      IntakeL.stop(vex::brakeType::brake);
      IntakeR.stop(vex::brakeType::brake);
      botRoller.stop();
      topRoller.stop();
      TilterNeedsStop = true;
    }

    // R1/R2 buttons control Intake
    if (Controller1.ButtonR2.pressing()) {
      IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      botRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      topRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeNeedsStop = false;
    } else if (Controller1.ButtonR1.pressing()) {
      IntakeL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      botRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      topRoller.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      IntakeNeedsStop = false;
    } else if (!IntakeNeedsStop) {
      IntakeL.stop(vex::brakeType::brake);
      IntakeR.stop(vex::brakeType::brake);
      botRoller.stop();
      topRoller.stop();
      IntakeNeedsStop = true;
    }
    //X/B for Tilter
    if (Controller1.ButtonX.pressing()) {
      TilterNeedsStop = false;
      Tilter.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
    if (Tilter.position(deg) >= 1000) {        
        IntakeL.spin(vex::directionType::fwd, 5, vex::velocityUnits::pct);
        IntakeR.spin(vex::directionType::fwd, 5, vex::velocityUnits::pct);
      }
    } else if (Controller1.ButtonB.pressing()) {
      Tilter.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
      IntakeL.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
      IntakeR.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
      TilterNeedsStop = false;
    } else if (!TilterNeedsStop) {
      Tilter.stop(vex::brakeType::brake);
      IntakeL.stop(brakeType::brake);
      IntakeR.stop(brakeType::brake);
      TilterNeedsStop = true;
    }
    if (Controller1.ButtonY.pressing()) {
      // centerBlock();
    }

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

// clears values but puts position degrees for drive
void clearValues ( void ) {
  Tilter.setPosition(0, degrees);
  LeftDrive.setPosition(0, degrees);
  RightDrive.setPosition(0, degrees);
  // ArmL.setPosition(0, degrees);
}

void values ( void ) {
  static double     frightCurrent;
  static double     frightEfficiency;
  static double     frightPower;
  static double     frightVoltage;
  static double     ballval;
  while (true) {
    
    Brain.Screen.printAt( 10, 20, "Obj dist %f", detec.objectDistance(distanceUnits::in) );
    Brain.Screen.printAt( 10, 40, "Obj size %f", detec.objectSize() );
    Brain.Screen.printAt( 10, 60, "Obj vel %f", detec.objectVelocity() );
  
  }
}

/*
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * This should be called at the start of your int main function.
 */

void vexcodeInit( void ) {
  clearValues();
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
}