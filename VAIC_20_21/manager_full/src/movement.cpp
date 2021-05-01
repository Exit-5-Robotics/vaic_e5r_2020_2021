#include "vex.h"

using namespace vex;

const int rollerDistance = 400;
const int intakeDriveSpeed = 10;
int distPosition = 1;


void stopDriving( void ) {
  robotDrive.stop();
  driving = false;
}

void lookAround( void ) {
  robotDrive.turnFor(right, 360, degrees, 10, velocityUnits::pct);
  task::sleep(10000);
  stopDriving();
}

void intake( int speed ) {
  while (ballThree.value(analogUnits::mV) > 3300) {
    Brain.Screen.printAt(20, 180, "%d", ballThree.value(analogUnits::mV));
    robotDrive.drive(fwd, speed, vex::velocityUnits::pct);
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  stopDriving();
  intakeWheels.spinFor(fwd, 720, degrees, 60, vex::velocityUnits::pct);
  intakeWheels.stop();
}

void intakeNoDrive() {
  while (ballThree.value(analogUnits::mV) > 3300) {
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  intakeWheels.stop();
}

void outtake() {
  // leftIntake.spinFor(rev, double rotation, vex::rotationUnits::deg, double velocity, velocityUnits units_v);
  // rightIntake.spinFor(rev, double rotation, vex::rotationUnits::deg, double velocity, velocityUnits units_v);
}

int score() {
  // ONLY RUN IF THE DESIRED SCORED BALL IS IN POSITION 3/ARRAY INDEX 0
  robotDrive.drive(fwd, 10, velocityUnits::pct);
  botRoller.spin(fwd, 100, vex::velocityUnits::pct);
  topRoller.spin(fwd, 100, vex::velocityUnits::pct);
  task::sleep(2000);
  stopDriving();
  return 0;
}

void poop() {
  // ONLY RUN IF THE DESIRED POOPED BALL IS IN POSITION 2/ARRAY INDEX 1
  botRoller.spinFor(fwd, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct, false);
  topRoller.spinFor(reverse, rollerDistance, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}

void descore() {
  while(!goal.pressing()) robotDrive.drive(fwd, 30, vex::velocityUnits::pct);
  intake(intakeDriveSpeed);
  robotDrive.driveFor(reverse, 10, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
}

void pickUpClosest( std::string ballPos ) {
  // TODO
  goToX(stringToX(ballPos), stringToY(ballPos), local_heading); // ADJUST FOR ROBOT ADJUST FOR ROBOT ADJUST FOR ROBOT ADJUST FOR ROBOT
  // intake(intakeDriveSpeed);
  // robotDrive.driveFor(fwd, dist, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
}

int adjustHold() {
  while (ballZero.value(analogUnits::mV) > 3400) {
    botRoller.spin(fwd, 100, vex::velocityUnits::pct);
    topRoller.spin(fwd, 100, vex::velocityUnits::pct);
  }
  botRoller.stop();
  topRoller.stop();
  return 0;
}

void moveBackFromBall( fifo_object_box boxObj ) {
  // back up to 20 inches
  while (boxObj.depth/25.4 < 20)
    driveAngle(180, 20);
  stopDriving();
}

void centerBall( fifo_object_box boxObj ) {
  // center by driving sideways
  static MAP_RECORD currentMap;
  jetson_comms.get_data( &currentMap );
  
}

int centerGoal() {
  int goalX = 160;
  int directionDrive, diff, currentBox = 5;

  if (local_map.boxnum > 0) {
    for(int i=0;i<4;i++ ) {
      if( i < local_map.boxnum ) {
        if (local_map.boxobj[i].classID == 2) currentBox = i;
        break;
      }
    }
    if (currentBox != 5) {
      diff = goalX - local_map.boxobj[currentBox].x;
      while (abs(diff) > 5) {
        for(int i=0;i<4;i++ ) {
          if( i < local_map.boxnum ) {
            if (local_map.boxobj[i].classID == 2) currentBox = i;
            break;
          }
        }
        diff = goalX - local_map.boxobj[currentBox].x;
        directionDrive = (diff > 0) ? 0 : 180;
        driveAngle(90+directionDrive, 10);
      }
    }
  }

  return 0;
}

int moveDistSensor( int direc ) {
  distMotor.spinFor(direc*-300, degrees, 100, velocityUnits::pct);
  return direc;
}

void distSensorControl( void ) {
  int objDistance = dist.objectDistance(distanceUnits::mm);
  while (true) {
    objDistance = dist.objectDistance(distanceUnits::mm);
    if (objDistance < 200 && distPosition == -1) {
      distPosition = moveDistSensor(UP);
      this_thread::sleep_for(5000);
    } else if (objDistance > 200 && distPosition == 1) { // issue because when it goes up, does not see object any more
      distPosition = moveDistSensor(DOWN);
    } else {
      distMotor.stop();
    }
  }
}

void idiot() {
  centerBall(local_map.boxobj[0]);
  intake(10);
}

int testMovement() { // just for testing

  // intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  
  // while(true) {
  //   robotDrive.drive(fwd, 10, velocityUnits::pct);
  //   Brain.Screen.printAt(10, 20, "%f", tilt.acceleration(axisType::xaxis));
  // }
  // robotDrive.stop();
  
  // while (ballThree.value(analogUnits::mV) > 3300) robotDrive.drive(fwd, 5, velocityUnits::pct);
  
  
  while (true) {
    // if (local_x != 0) {
    //   task::sleep(15000);
    //   redIsolation();
    // }

    // if (local_heading != 0) {
    //   centerGoal();
    // }

    this_thread::sleep_for(16);
  }
  return 0;
}