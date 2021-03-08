#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::message_link LinkA( PORT11, "vex_robotics_team_3063_A", linkType::worker );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
motor RF = motor(PORT12, ratio18_1, false);
motor RB = motor(PORT14, ratio18_1, false);
motor LF = motor(PORT18, ratio18_1, false);
motor LB = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);
motor Motor8 = motor(PORT8, ratio18_1, false);
motor Motor9 = motor(PORT9, ratio18_1, true);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}