#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RF = motor(PORT12, ratio18_1, false);
motor RB = motor(PORT14, ratio18_1, false);
motor LF = motor(PORT18, ratio18_1, false);
motor LB = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);
motor Motor8 = motor(PORT8, ratio18_1, false);
motor Motor9 = motor(PORT9, ratio18_1, true);
motor Motor10 = motor(PORT10, ratio18_1, false);

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