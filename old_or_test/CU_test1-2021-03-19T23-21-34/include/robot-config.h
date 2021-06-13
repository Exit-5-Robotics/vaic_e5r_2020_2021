using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor IntakeL;
extern motor LF;
extern motor Index1;
extern motor Index2;
extern motor LB;
extern motor RB;
extern motor RF;
extern motor IntakeR;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );