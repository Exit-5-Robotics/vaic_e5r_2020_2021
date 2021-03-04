using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor Tilter;
extern drivetrain Drivetrain;
extern controller Controller1;
extern motor IntakeL;
extern motor IntakeR;
extern motor_group LeftDrive;
extern motor_group RightDrive;
extern signature SIG_ORANGE;
extern signature SIG_GREEN;
extern signature SIG_PURPLE;
extern signature SIG_4;
extern signature SIG_5;
extern signature SIG_6;
extern signature SIG_7;
extern vision Vision;
extern inertial Inertial;
extern line ball;

void values( void );
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void );