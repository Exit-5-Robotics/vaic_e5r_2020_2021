#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::message_link LinkA( PORT11, "vex_robotics_team_3063_A", linkType::manager );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
// sonar Balls = sonar(Brain.ThreeWirePort.B); // A is the output, B is the input https://api.vexcode.cloud/v5/html/classvex_1_1sonar.html#aeefdd6cb8826338561d0cf187643b14a
line ball = line(Brain.ThreeWirePort.C);
motor leftIntake = motor(PORT9, ratio18_1, false);
motor rightIntake = motor(PORT8, ratio18_1, true);
motor_group intakeWheels( leftIntake, rightIntake );
motor botRoller = motor(PORT1, ratio18_1, false);
motor topRoller = motor(PORT2, ratio18_1, false);
motor backLeftWheel = motor(PORT16, ratio18_1, false);
motor frontLeftWheel = motor(PORT17, ratio18_1, false);
motor backRightWheel = motor(PORT18, ratio18_1, true);
motor frontRightWheel = motor(PORT19, ratio18_1, true);
motor_group   leftDrive( backLeftWheel, frontLeftWheel );
motor_group   rightDrive( backRightWheel, frontRightWheel );
inertial      tilt( PORT10 );
smartdrive    robotDrive( leftDrive, rightDrive, tilt, 12.56, 14.125, 9, distanceUnits::in ); // might have to change values

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
  if (OUR_COLOR == RED) {
    
  } else if (OUR_COLOR == BLUE) {

  }
}