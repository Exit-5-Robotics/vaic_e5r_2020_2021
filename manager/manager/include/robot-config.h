using namespace vex;

extern brain Brain;
extern message_link LinkA;
extern sonar Balls;
extern motor botRoller;
extern motor topRoller;

void ball_detect_stop_bot(float dist);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
