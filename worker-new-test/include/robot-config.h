using namespace vex;

// VEXcode devices

extern brain Brain;
extern message_link LinkA;
extern motor RF;
extern motor RB;
extern motor LF;
extern motor LB;
extern motor roller;
extern motor intakeLeft;
extern motor intakeRight;
extern motor_group intake;
extern motor_group pooper;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern motor_group leftDiagDrive;
extern motor_group rightDiagDrive;
extern inertial tilt;
extern line ballChecker;
extern line rightLine;
extern line leftLine;
extern bumper   goal;
extern bumper   backStopper;
extern smartdrive robotDrive;
extern motor middleDescorer;

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

