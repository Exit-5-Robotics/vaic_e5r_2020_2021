#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::message_link LinkA( PORT9, "vex_robotics_team_3063_A", linkType::manager );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
// sonar Balls = sonar(Brain.ThreeWirePort.B); // A is the output, B is the input https://api.vexcode.cloud/v5/html/classvex_1_1sonar.html#aeefdd6cb8826338561d0cf187643b14a
line          ballThree(Brain.ThreeWirePort.C);
line          ballZero(Brain.ThreeWirePort.E);
motor         leftIntake(PORT1, ratio18_1, false);
motor         rightIntake(PORT19, ratio18_1, true);
motor_group   intakeWheels( leftIntake, rightIntake );
motor         botRoller(PORT11, ratio18_1, false);
motor         topRoller(PORT12, ratio18_1, false);
motor         backLeftWheel(PORT16, ratio18_1, false);
motor         frontLeftWheel(PORT2, ratio18_1, false);
motor         backRightWheel(PORT17, ratio18_1, true);
motor         frontRightWheel(PORT18, ratio18_1, true);
motor_group   leftDrive( backLeftWheel, frontLeftWheel );
motor_group   rightDrive( backRightWheel, frontRightWheel );
inertial      tilt( PORT10 );
bumper        goal(Brain.ThreeWirePort.D);
smartdrive    robotDrive( leftDrive, rightDrive, tilt, 12.56, 14.125, 9, distanceUnits::in ); // might have to change values

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