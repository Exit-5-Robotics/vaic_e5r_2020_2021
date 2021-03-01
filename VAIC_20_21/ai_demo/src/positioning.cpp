#include "vex.h"

using namespace vex;


void turnTo( float dest_heading, int vel ) {
  
  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  float change = dest_heading - (current_heading*180/M_PI + 180);
  change = change > 0 ? change : change + 360;

  if (change < 180) {
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  } else {
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct);
  }
  
}

static void goTo( float dest_x, float dest_y, float dest_heading ) {

  float x, y, heading;
  link.get_local_location(x, y, heading);

  // convert units to inches and degrees
  x /= 25.4;
  y /= 25.4;
  heading *= 180/M_PI + 180;

  float change_x = dest_x - x;
  float change_y = dest_y - y;

  double turnToAngle = (90 - atan((double)change_y/(double)change_x)*180/M_PI);

  turnTo(turnToAngle, 10);
  
  robotDrive.driveFor(sqrt((double)pow(change_x, 2) + (double)pow(change_y,2)), vex::distanceUnits::in, 10, vex::velocityUnits::pct);
  
  turnTo(dest_heading, 10);

}

int driveTo() {
  while (true) {
    float current_x, current_y, current_heading;
    link.get_local_location(current_x, current_y, current_heading);
    if (current_x != 0) {
      vex::task::sleep(2000);
      goTo(30, 30, 0);
    }
    Brain.Screen.render();
    this_thread::sleep_for(16);
  }
  return 0;
}