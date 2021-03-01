#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::message_link LinkA( PORT11, "vex_robotics_team_3063_A", linkType::manager );
// vex::serial_link LinkB( PORT12, "vex_robotics_team_1234_B", linkType::manager );
// vex::message_link LinkC( PORT11, "vex_robotics_team_1234_A", linkType::worker );
// vex::serial_link LinkD( PORT12, "vex_robotics_team_1234_B", linkType::worker );
// sonar Balls = sonar(Brain.ThreeWirePort.B); // A is the output, B is the input https://api.vexcode.cloud/v5/html/classvex_1_1sonar.html#aeefdd6cb8826338561d0cf187643b14a
line ball = line(Brain.ThreeWirePort.C);
motor leftIntake = motor(PORT9, ratio18_1, false);
motor rightIntake = motor(PORT8, ratio18_1, true);
motor_group intakeWheels( leftIntake, rightIntake );
motor botRoller = motor(PORT1, ratio18_1, false);
motor topRoller = motor(PORT2, ratio18_1, false);
motor backLeftWheel = motor(PORT16, ratio18_1, false);
motor frontLeftWheel = motor(PORT17, ratio18_1, false);
motor backRightWheel = motor(PORT18, ratio18_1, true);
motor frontRightWheel = motor(PORT19, ratio18_1, true);
motor_group   leftDrive( backLeftWheel, frontLeftWheel );
motor_group   rightDrive( backRightWheel, frontRightWheel );
inertial      tilt( PORT10 );
smartdrive    robotDrive( leftDrive, rightDrive, tilt, 12.56, 14.125, 9, distanceUnits::in ); // might have to change values

// void ball_detect_stop_bot( float dist ) {
//   while (Balls.distance(vex::distanceUnits::in) > dist) {
//     botRoller.setVelocity(100, vex::percentUnits::pct);
//     botRoller.spin(fwd);
//   }
//   botRoller.stop();
// }

static void goTo( float dest_x, float dest_y, float dest_heading ) {

  float x, y, heading;
  link.get_local_location(x, y, heading);
  heading *= 180/M_PI;

  float change_y = dest_y - y / 25.4;
  Brain.Screen.printAt(10, 20, "Change y: %f", change_y);
  Brain.Screen.printAt(10, 40, "y: %f", dest_y);
  Brain.Screen.printAt(10, 60, "Current y: %f %f", y, y/25.4);
  
  float change_x = dest_x - x / 25.4;
  Brain.Screen.printAt(10, 80, "Change x: %f", change_x);
  Brain.Screen.printAt(10, 100, "x: %f", dest_x);
  Brain.Screen.printAt(10, 120, "Current x: %f %f", x, x/25.4);

  double turnToAngle = round(270 - atan((double)change_y/(double)change_x)*180/M_PI);
  Brain.Screen.printAt(10, 140, "Arctan: %f", atan((double)change_y/(double)change_x)*180/M_PI);
  Brain.Screen.printAt(10, 160, "Current Heading: %f", heading);
  Brain.Screen.printAt(10, 180, "Turn angle: %f", turnToAngle);

  // robotDrive.turnToRotation(turnToAngle, rotationUnits::deg, 10, vex::velocityUnits::pct);

  // // while ( std::abs(current_x - x) > 20 ) {
  // //   robotDrive.drive(fwd, 30, vex::velocityUnits::pct);
  // //   link.get_local_location(current_x, current_y, current_headi
  
  // // robotDrive.stop(brake);

  // // alternative
  // robotDrive.driveFor(sqrt((double)pow(change_x, 2) + (double)pow(change_y,2)), vex::distanceUnits::in, 10, vex::velocityUnits::pct);
  // Brain.Screen.printAt(10, 200, "Drive for: %f", sqrt((double)pow(change_x, 2) + (double)pow(change_y,2)));
  
  // robotDrive.turnToRotation(dest_heading, rotationUnits::deg, 10, vex::velocityUnits::pct);
}

int driveTo() {
  while (true) {
    float current_x, current_y, current_heading;
    link.get_local_location(current_x, current_y, current_heading);
    if (current_x != 0) {
      goTo(10, 10, 0);
      vex::task::sleep(20000);

      std::terminate();
    }
  }
  return 0;
}

void intake() {
  // ONLY RUN IF WHEEL EFFICIENCY AND CURRENT ARE BOTH 0
  while (ball.value(analogUnits::mV) > 3300) {
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
    intakeWheels.spinFor(fwd, 1000, degrees, 80, vex::velocityUnits::pct);
}

void outtake() {
  // leftIntake.spinFor(rev, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
  // rightIntake.spinFor(rev, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
}

void score() {
  // botRoller.spinFor(fwd, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
  // topRoller.spinFor(fwd, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
}

void poop() {
  // botRoller.spinFor(fwd, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
  // topRoller.spinFor(rev, double rotation, rotationUnits units, double velocity, velocityUnits units_v);
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
  if (OUR_COLOR == RED) {
    
  } else if (OUR_COLOR == BLUE) {

  }
}