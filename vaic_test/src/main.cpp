/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\rachelle.hu                                      */
/*    Created:      Sun Nov 17 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// Tilter               motor         11
// Drivetrain           drivetrain    12, 20
// LeftDrive            motor         12
// RightDrive           motor         20
// IntakeL              motor         1
// IntakeR              motor         10
// Arms                 motor         3, 4
// MiddleWheel          motor         13 (forward is to left)
// Vision               vision        14
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vision.h"
#define RED 1
#define BLUE -1
#define RANGLE -1
#define BANGLE 0

using namespace vex;

competition Competition;

// double pi = acos(-1);
void back( int side );
void front(int side );
// void centerBlock();

void pre_auton( void ) {
  // DO NOT REMOVE!
  vexcodeInit();
}

void autonomous( void ) {
  // ArmL.spin(reverse);
  // ArmR.spin(reverse);
  // Drivetrain.driveFor(directionType::fwd, 15, inches, 80, velocityUnits::pct);
  // Drivetrain.driveFor(directionType::rev, 15, inches, 80, velocityUnits::pct);
  // ArmL.spinFor(directionType::fwd, 400, rotationUnits::deg, 100, velocityUnits::pct, false);
  // ArmR.spinFor(directionType::fwd, 400, rotationUnits::deg, 100, velocityUnits::pct, false);
  // Tilter.spinFor(directionType::fwd, 100, rotationUnits::deg, 100, velocityUnits::pct);
  // Tilter.spinFor(directionType::rev, 100, rotationUnits::deg, 100, velocityUnits::pct);
  // task::sleep(1000);
  // ArmL.spinFor(directionType::rev, 400, rotationUnits::deg, 70, velocityUnits::pct, false);
  // ArmR.spinFor(directionType::rev, 400, rotationUnits::deg, 70, velocityUnits::pct);
  // ArmL.stop(brakeType::coast);
  // ArmR.stop(brakeType::coast);
  // Tilter.stop();
  // task::sleep(500);
  // back(BLUE);
  // // front(RED);
}

void usercontrol( void ) {
}

int main() {
  
  thread t1(values);

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}






// MODULAR FUNCTIONS BELOW | MODULAR FUNCTIONS BELOW | MODULAR FUNCTIONS BELOW | MODULAR FUNCTIONS BELOW
void front ( int side ) {
  IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  
  Drivetrain.driveFor(directionType::fwd, 5, inches, 20, velocityUnits::pct);

}

void back ( int side ) {
  IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  IntakeL.stop(brakeType::brake);
  IntakeR.stop(brakeType::brake);
  
  Tilter.spinFor(vex::directionType::fwd, 375, deg, 10, vex::velocityUnits::pct, false);
  vex::task::sleep(2000);
  while (Tilter.isSpinning()) {
    IntakeL.spin(vex::directionType::rev, 5, vex::velocityUnits::pct);
    IntakeR.spin(vex::directionType::rev, 5, vex::velocityUnits::pct);
  }
  IntakeL.stop();
  IntakeR.stop();
  for (int i=0; i<50; i++) {
    LeftDrive.spinFor(directionType::rev, 20, rotationUnits::deg);
    RightDrive.spinFor(directionType::rev, 20, rotationUnits::deg);
  }
}