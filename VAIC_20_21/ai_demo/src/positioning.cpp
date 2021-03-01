#include "vex.h"

using namespace vex;


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
      vex::task::sleep(200000);
    }
    Brain.Screen.render();
    this_thread::sleep_for(16);
  }
  return 0;
}