#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Motor1 = motor(PORT1, ratio18_1, false);
motor Motor2 = motor(PORT2, ratio18_1, false);
motor Motor3 = motor(PORT3, ratio18_1, true);
motor Motor8 = motor(PORT8, ratio18_1, true);
motor Motor9 = motor(PORT9, ratio6_1, false);
motor Motor16 = motor(PORT16, ratio18_1, false);
motor Motor17 = motor(PORT17, ratio18_1, false);
motor Motor18 = motor(PORT18, ratio18_1, true);
motor Motor19 = motor(PORT19, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}