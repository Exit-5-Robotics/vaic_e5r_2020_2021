#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
message_link  LinkA( PORT9, "vex_robotics_team_3063_A", linkType::manager );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
// sonar Balls = sonar(Brain.ThreeWirePort.B); // A is the output, B is the input https://api.vexcode.cloud/v5/html/classvex_1_1sonar.html#aeefdd6cb8826338561d0cf187643b14a
line          ballThree(Brain.ThreeWirePort.C);
line          ballZero(Brain.ThreeWirePort.E);
vex::distance dist(PORT5);
motor         leftIntake(PORT1, ratio18_1, false);
motor         rightIntake(PORT19, ratio18_1, true);
motor_group   intakeWheels( leftIntake, rightIntake );
motor         botRoller(PORT11, ratio18_1, false);
motor         topRoller(PORT12, ratio18_1, false);
motor         distMotor(PORT8, ratio18_1, true);
motor         backLeftWheel(PORT16, ratio18_1, false);
motor         frontLeftWheel(PORT2, ratio18_1, true);
motor         backRightWheel(PORT17, ratio18_1, true);
motor         frontRightWheel(PORT18, ratio18_1, false);
motor_group   leftDrive( backLeftWheel, frontLeftWheel );
motor_group   rightDrive( backRightWheel, frontRightWheel );
motor_group   rightDiagDrive( frontLeftWheel, backRightWheel );
motor_group   leftDiagDrive( frontRightWheel, backLeftWheel );
inertial      tilt( PORT10 );
// bumper        goal(Brain.ThreeWirePort.D);
smartdrive    robotDrive( leftDrive, rightDrive, tilt, 12.56, 14.125, 9, distanceUnits::in ); // might have to change values

controller Controller1 = controller(primary); // 
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  if (OUR_COLOR == RED) {
    tilt.setHeading(270, deg);
  } else if (OUR_COLOR == BLUE) {
    tilt.setHeading(90, deg);
  }
}

// COPIED FROM PRIOR DRIVING PROGRAM
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
    int drivetrainSide = Controller1.Axis4.position();
    int drivetrainPerspective = Controller1.Axis1.position();
    // check if the value is inside of the deadband range
    if (drivetrainForwardBackward < 5 && drivetrainForwardBackward > -5) { //////////
      // check if the motor has already been stopped
      if (DrivetrainNeedsToBeStopped_Controller1) {
        leftDrive.stop(vex::brakeType::brake);
        rightDrive.stop(vex::brakeType::brake);
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
          leftDrive.setVelocity(pow(drivetrainForwardBackward, 2) / 1.2*drivetrainForwardBackward, percent);
          rightDrive.setVelocity(pow(drivetrainForwardBackward, 2) / 1.2*drivetrainForwardBackward, percent);
        }
        leftDrive.setVelocity(drivetrainForwardBackward, percent);
        rightDrive.setVelocity(drivetrainForwardBackward, percent);
      } else {
        leftDrive.setVelocity(drivetrainForwardBackward/5, percent);
        rightDrive.setVelocity(drivetrainForwardBackward/5, percent);
      }
      leftDrive.spin(fwd);
      rightDrive.spin(fwd);
    }
    // deadband?? yeenaw
    if (drivetrainPerspective < 5 && drivetrainPerspective > -5) {
      if (turnyturnNeedsToBeStopped_Controller1) {
        leftDrive.stop(vex::brakeType::brake);
        rightDrive.stop(vex::brakeType::brake);
        // tell the code that the motors been stopped
        turnyturnNeedsToBeStopped_Controller1 = false;
      }
    } else {
      turnyturnNeedsToBeStopped_Controller1 = true;
    }
    if (turnyturnNeedsToBeStopped_Controller1) {
      if (DriveSpeed) {
        leftDrive.setVelocity(drivetrainPerspective, pct);
        rightDrive.setVelocity(drivetrainPerspective, pct);
      } else {
        leftDrive.setVelocity(drivetrainPerspective/5, pct);
        rightDrive.setVelocity(drivetrainPerspective/5, pct);
      }
      leftDrive.spin(fwd);
      rightDrive.spin(reverse);
    }
    // Up/Down buttons control Arms
    if (Controller1.ButtonL1.pressing()) {
      leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      TilterNeedsStop = false;
    } else if (Controller1.ButtonL2.pressing()) {
      leftIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      TilterNeedsStop = false;
    } else if (!TilterNeedsStop) {
      leftIntake.stop(vex::brakeType::brake);
      rightIntake.stop(vex::brakeType::brake);
      botRoller.stop();
      topRoller.stop();
      TilterNeedsStop = true;
    }

    // R1/R2 buttons control Intake
    if (Controller1.ButtonR2.pressing()) {
      leftIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      botRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      topRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeNeedsStop = false;
    } else if (Controller1.ButtonR1.pressing()) {
      leftIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      rightIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      botRoller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      topRoller.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      IntakeNeedsStop = false;
    } else if (!IntakeNeedsStop) {
      leftIntake.stop(vex::brakeType::brake);
      rightIntake.stop(vex::brakeType::brake);
      botRoller.stop();
      topRoller.stop();
      IntakeNeedsStop = true;
    }
    // //X/B for Tilter
    // if (Controller1.ButtonX.pressing()) {
    //   TilterNeedsStop = false;
    //   Tilter.spin(vex::directionType::fwd, 30, vex::velocityUnits::pct);
    // if (Tilter.position(deg) >= 1000) {        
    //     leftIntake.spin(vex::directionType::fwd, 5, vex::velocityUnits::pct);
    //     rightIntake.spin(vex::directionType::fwd, 5, vex::velocityUnits::pct);
    //   }
    // } else if (Controller1.ButtonB.pressing()) {
    //   Tilter.spin(vex::directionType::rev, 80, vex::velocityUnits::pct);
    //   leftIntake.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
    //   rightIntake.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
    //   TilterNeedsStop = false;
    // } else if (!TilterNeedsStop) {
    //   Tilter.stop(vex::brakeType::brake);
    //   leftIntake.stop(brakeType::brake);
    //   rightIntake.stop(brakeType::brake);
    //   TilterNeedsStop = true;
    // }
    // if (Controller1.ButtonY.pressing()) {
    //   // centerBlock();
    // }

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

// clears values but puts position degrees for drive
void clearValues ( void ) {
  leftDrive.setPosition(0, degrees);
  rightDrive.setPosition(0, degrees);
  // ArmL.setPosition(0, degrees);
}

// void values ( void ) {
//   while (true) {
//     Brain.Screen.printAt(10, 20, "Object distance: %f", objDetector.objectDistance(distanceUnits::in));
//     Brain.Screen.printAt(10, 40, "Object size: %d", objDetector.objectRawSize());
//     Brain.Screen.printAt(10, 60, "Object velocity: %f", objDetector.objectVelocity());
//   }
// }