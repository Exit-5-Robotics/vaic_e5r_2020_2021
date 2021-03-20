using namespace vex;

extern brain Brain;
extern message_link LinkA;
extern sonar Balls;
extern line ballThree;
extern line ballZero;
extern motor leftIntake;
extern motor rightIntake;
extern motor_group intakeWheels;
extern motor botRoller;
extern motor topRoller;
extern motor backLeftWheel;
extern motor frontLeftWheel;
extern motor backRightWheel;
extern motor frontRightWheel;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern inertial tilt;
extern bumper goal;
extern smartdrive robotDrive;

void driveAngle( int angleToDrive, int speed );
void driveAngleAbs( int angleToDrive, int speed );
void driveAngleFor( int dist, int angleToDrive, int speed );
void driveAngleForAbs( int dist, int angleToDrive, int speed );
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
void values( void );