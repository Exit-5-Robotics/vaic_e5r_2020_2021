using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor RF;
extern motor RB;
extern motor LF;
extern motor LB;
extern controller Controller1;
extern motor Motor8;
extern motor Motor9;
extern motor Motor10;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );