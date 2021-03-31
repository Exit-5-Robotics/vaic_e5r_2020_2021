#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::message_link LinkA( PORT11, "vex_robotics_team_3063_A", linkType::worker );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
controller Controller1 = controller(primary);

motor RF = motor(PORT12, ratio18_1, false);
motor RB = motor(PORT14, ratio18_1, false);
motor LF = motor(PORT18, ratio18_1, false);
motor LB = motor(PORT13, ratio18_1, false);

motor_group leftDrive(LF, LB);
motor_group rightDrive(RF, RB);
motor_group leftDiagDrive(LB, RF);
motor_group rightDiagDrive(LF, RB);

motor roller = motor(PORT10, ratio18_1, true);
motor intakeRight = motor(PORT8, ratio18_1, true);
motor intakeLeft = motor(PORT7, ratio18_1, false);
motor_group intake (intakeLeft, intakeRight);
motor_group pooper(roller, intakeLeft, intakeRight);

inertial      tilt(PORT5);
line          ballChecker(Brain.ThreeWirePort.H);
bumper        goal(Brain.ThreeWirePort.A);
/*                                                       A      B    C              */
smartdrive    robotDrive( leftDrive, rightDrive, tilt, 12.56, 7.75, 10.9, distanceUnits::in ); 
  // A: circumference
  // B: width
  // C: length

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}