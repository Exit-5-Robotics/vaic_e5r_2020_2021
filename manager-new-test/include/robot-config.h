using namespace vex;

extern brain Brain;
extern message_link LinkA;
extern sonar Balls;
extern line ballThree;
extern line ballZero;
extern vex::distance dist;
extern motor leftIntake;
extern motor rightIntake;
extern motor_group intakeWheels;
extern motor botRoller;
extern motor topRoller;
extern motor distMotor;
extern motor LB;
extern motor LF;
extern motor RB;
extern motor RF;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern motor_group rightDiagDrive;
extern motor_group leftDiagDrive;
extern line rightLine;
extern line leftLine;
extern inertial tilt;
extern bumper goal;
extern smartdrive robotDrive;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
void values( void );