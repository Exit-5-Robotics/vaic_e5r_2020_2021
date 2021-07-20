#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::message_link LinkA( PORT11, "vex_robotics_team_3063_A", linkType::worker );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
controller Controller1 = controller(primary);

motor RF = motor(PORT1, ratio18_1, false);
motor RB = motor(PORT15, ratio18_1, false);
motor LF = motor(PORT6, ratio18_1, true);
motor LB = motor(PORT16, ratio18_1, true);

motor_group leftDrive(LB, LF);
motor_group rightDrive(RB, RF);
motor_group leftDiagDrive(LB, RF);
motor_group rightDiagDrive(LF, RB);

motor roller = motor(PORT10, ratio18_1, true);
motor intakeRight = motor(PORT8, ratio18_1, false);
motor intakeLeft = motor(PORT19, ratio18_1, true);
motor_group intakeArms (intakeLeft, intakeRight);
motor_group pooper(roller, intakeLeft, intakeRight);
motor storer = motor (PORT11, ratio18_1, true);
motor_group bothRollers (roller, storer);
motor shelf = motor(PORT12, true);

inertial      tilt(PORT14);
line          ballChecker(Brain.ThreeWirePort.H);
optical       forLine(PORT20);
//distance      ballChecker(PORT2);
line          rightLine(Brain.ThreeWirePort.F);
line          leftLine(Brain.ThreeWirePort.G);
bumper        goal(Brain.ThreeWirePort.C);
bumper        backStopper(Brain.ThreeWirePort.B); //UPDATE THIS PLZ

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