using namespace vex;

extern brain Brain;
extern message_link LinkA;
extern sonar Balls;
extern motor leftIntake;
extern motor rightIntake;
extern motor botRoller;
extern motor topRoller;
extern motor backLeftWheel;
extern motor frontLeftWheel;
extern motor backRightWheel;
extern motor frontRightWheel;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern inertial tilt;
extern smartdrive robotDrive;

void ball_detect_stop_bot(float dist);
void goTo( float x, float y, float heading );

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);