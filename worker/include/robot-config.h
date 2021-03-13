using namespace vex;

// VEXcode devices

extern brain Brain;
extern message_link LinkA;
extern motor RF;
extern motor RB;
extern motor LF;
extern motor LB;
extern motor roller;
extern motor intake; 


/*
extern brain Brain;
extern message_link LinkA;
extern motor RF;
extern motor RB;
extern motor LF;
extern motor LB;
extern motor roller;
extern motor intake;

motor RF = motor(PORT12);
motor RB = motor(PORT14);
motor LF = motor(PORT18);
motor LB = motor(PORT13);
motor roller = motor(PORT8);
motor intake = motor(PORT9);
*/



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */

void vexcodeInit(void);

