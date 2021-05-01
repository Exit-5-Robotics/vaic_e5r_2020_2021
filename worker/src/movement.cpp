#include "vex.h"
#include <cmath>

using namespace vex;

void driveAngle( int angleToDrive, int speed ) {
  // drive at an angle relative to the current angle of the robot
  int measureAngle = (angleToDrive + 45)%360;
  int tempAngle;
  float rightSpeed, leftSpeed;
  switch (measureAngle/90) {
    case 0:
      tempAngle = 90 - measureAngle;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(fwd, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(fwd, leftSpeed, velocityUnits::pct);
      // both L and R are positive
      break;
    case 1:
      // R is positive, L is negative
      tempAngle = measureAngle - 90;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(fwd, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(reverse, leftSpeed, velocityUnits::pct);
      break;
    case 2:
      // both L and R are negative
      tempAngle = 270 - measureAngle;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(reverse, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(reverse, leftSpeed, velocityUnits::pct);
      break;
    default:
      // L is positive, R is negative
      tempAngle = measureAngle - 270;
      rightSpeed = speed*cos(tempAngle/(180/M_PI));
      leftSpeed = speed*sin(tempAngle/(180/M_PI));
      rightDiagDrive.spin(reverse, rightSpeed, velocityUnits::pct);
      leftDiagDrive.spin(fwd, leftSpeed, velocityUnits::pct);
      break;
  }
}

void driveAngleAbs( int angleToDrive, int speed ) {
  // drive at an absolute angle
  // get starting location and heading (mainly just heading)
  float start_x, start_y, start_heading;
  link.get_local_location(start_x, start_y, start_heading);
  // convert to degrees
  start_heading *= 180/M_PI;
  start_heading += 180;

  // find angle to drive at relative to current heading
  int relativeDriveAngle = (angleToDrive - (int)start_heading)%360;
  if (relativeDriveAngle < 0) relativeDriveAngle += 360;
  
  driveAngle(relativeDriveAngle, speed);
}

void driveAngleFor( int dist, int angleToDrive, int speed ) {
  // drive at an angle for a distance in inches relative to current angle of robot
  int degreesDrive = dist*47;
  int currentRotation = robotDrive.rotation(deg);
  driveAngle(angleToDrive, speed);
  while (sqrt(pow(rightDiagDrive.rotation(deg),2)+pow(leftDiagDrive.rotation(deg),2))-currentRotation < degreesDrive);
  robotDrive.stop();
}

void driveAngleForAbs( int dist, int angleToDrive, int speed ) {
  // drive at an absolute angle for a distance in inches
  float start_x, start_y, start_heading;
  link.get_local_location(start_x, start_y, start_heading);
  // convert to degrees
  start_heading *= 180/M_PI;
  start_heading += 180;

  // find angle to drive at relative to current heading
  int relativeDriveAngle = (angleToDrive - (int)start_heading)%360;
  
  driveAngleFor(dist, relativeDriveAngle, speed);
}


/******************************************TURN TO******************************************/


int turnTo( float dest_heading, int vel ) {
  Brain.Screen.printAt(0, 15, "one");
  float current_x, current_y, current_heading;
  //link.get_local_location(current_x, current_y, current_heading); //rachelle help the current_heading isn't working it just always says zero
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );
  current_heading = local_map.pos.az*180/M_PI;
  current_x = local_map.pos.x;
  current_y = local_map.pos.y;
  Brain.Screen.printAt(0,22, "%f", current_heading);

  float change = dest_heading - (current_heading + 180);
  Brain.Screen.printAt(0,34, "%f", change);
  change = change > 0 ? change : change + 360;
  Brain.Screen.printAt(0,44, "%f", change);

  if (change < 180) {
    Brain.Screen.printAt(0, 35, "two");
    robotDrive.turnFor(right, change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct, false);
    while (robotDrive.isTurning()) {
      static MAP_RECORD  local_map;
      jetson_comms.get_data( &local_map );
      current_heading = local_map.pos.az*180/M_PI;
      current_x = local_map.pos.x;
      current_y = local_map.pos.y;
      Brain.Screen.printAt(0,22, "%f", current_heading);
      if (abs((int)dest_heading - ((int)current_heading + 180)) < 5) {
        robotDrive.stop();
        Brain.Screen.printAt(0, 55, "three");
        return 0;
      }
    }
  } else {
    Brain.Screen.printAt(0, 75, "four");
    robotDrive.turnFor(left, 360 - change, vex::rotationUnits::deg, vel, vex::velocityUnits::pct, false);
    while (robotDrive.isTurning()) {
      Brain.Screen.printAt(0, 75, "four.five");
      static MAP_RECORD  local_map;
      jetson_comms.get_data( &local_map );
      current_heading = local_map.pos.az*180/M_PI;
      current_x = local_map.pos.x;
      current_y = local_map.pos.y;
      Brain.Screen.printAt(0,100, "%f", current_heading);
      if (abs((int)dest_heading - ((int)current_heading + 180)) < 10) {
        robotDrive.stop();
        Brain.Screen.printAt(0, 115, "five");
        this_thread::sleep_for(20000);
        return 0;
      }
    }
  }
  Brain.Screen.printAt(0, 135, "six");
  return 0;
}

/****************************************** SNAIL TURN TO ******************************************/

float toNormalAngle(float og_angle){
  if(og_angle < 0){
    return 360 - fabs(og_angle);
  }
  return og_angle;
}

void snailTo(float dest_heading){
  float current_heading;
  //rachelle help the current_heading isn't working it just always says zero
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );
  current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
  dest_heading = toNormalAngle(dest_heading);

  Brain.Screen.printAt(0,180, "1currentHeading  %f", current_heading);
  Brain.Screen.printAt(0,195, "1destHeading  %f", dest_heading);

  //choosing direction to turn
  if( fabs(current_heading - dest_heading) < 180){
    if(current_heading > dest_heading){
      driveAuto(3); //left
      Brain.Screen.printAt(0,15, "left-1");
    } else{
      driveAuto(2); //right
      Brain.Screen.printAt(0,15, "right-2");
    }
  } else{
    if(current_heading > dest_heading){
      driveAuto(2); //right
      Brain.Screen.printAt(0,15, "right-3");
    } else{
      driveAuto(3); //left
      Brain.Screen.printAt(0,15, "left-4");
    }
  }

  //stopping once it reaches a certain angle
  if(current_heading < dest_heading){
    if( fabs(current_heading - dest_heading) > 180 ){
      while(current_heading < 180 ){ //1
        //update but not with toNormalHeading
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
        Brain.Screen.printAt(0,140, "ONE POINT ONE");
      }
      while(current_heading > dest_heading){
        //update with toNormalAngle
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
        Brain.Screen.printAt(0,140, "ONE POINT TWO");
      }
    } else {
      while(current_heading < dest_heading){ //3
        //update with toNormalAngle
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
        Brain.Screen.printAt(0,140, "THREE");
      }
    }
  } else {
    if( fabs(current_heading - dest_heading) > 180 ){
      while(current_heading > 180){ //2
        //update but not with toNormalHeading
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
        Brain.Screen.printAt(0,140, "TWO POINT ONE");
      }
      while(current_heading < dest_heading){
        //update with toNormalAngle
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
        Brain.Screen.printAt(0,140, "TWO POINT TWO");
      }
    } else{
      while(current_heading > dest_heading){ //4
        //update with toNormalAngle
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        current_heading = toNormalAngle(local_map.pos.az*180/M_PI);
        dest_heading = toNormalAngle(dest_heading);
        Brain.Screen.printAt(0,140, "FOUR");
      }
    }
  }
  Brain.Screen.printAt(0, 160, "PAUSE FU");
  pause();
  Brain.Screen.printAt(0,210, "2currentHeading %f", current_heading);
}

/***************************************SIDE GO TO****************************************/

void sideGoTo(float finishCoordinate){ //MfinsihCoordinate is not in altered coordinate system

  float currentX, currentY, currentHeading;
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );
  currentHeading = local_map.pos.az*180/M_PI;
  currentX = local_map.pos.x + 1500;
  currentY = local_map.pos.y + 1500;
  Brain.Screen.printAt(0,115, "currentHeading  %f", currentHeading);
  Brain.Screen.printAt(0,130, "1currentX  %f", currentX-1500);
  Brain.Screen.printAt(0,145, "1currentY  %f", currentY-1500);
  finishCoordinate+= 1500;
  
  if(fabs(currentHeading) > 60 && fabs(currentHeading) < 110){ //moving along y axis 
    while(fabs(finishCoordinate - currentY) > 10){
      static MAP_RECORD  local_map;
      jetson_comms.get_data( &local_map );
      currentHeading = local_map.pos.az*180/M_PI;
      currentX = local_map.pos.x + 1500;
      currentY = local_map.pos.y + 1500;
      
      if( (currentY > finishCoordinate && currentHeading == fabs(currentHeading) /*facing window wall*/) || (currentY < finishCoordinate && fabs(currentHeading) != currentHeading/*facing whiteboard wall*/)){
        //drive to the left
        driveAuto(8);
        if(currentY > finishCoordinate){
          break;
        }
      }else{
        //drive to the right
        driveAuto(9);
        if(currentY < finishCoordinate){
          break;
        }
      }
    } 
  }else { // moving along x axis
    while(fabs(finishCoordinate - currentX) > 10){
      static MAP_RECORD  local_map;
      jetson_comms.get_data( &local_map );
      currentHeading = local_map.pos.az*180/M_PI;
      currentX = local_map.pos.x + 1500;
      currentY = local_map.pos.y + 1500;
      if((currentX > finishCoordinate && fabs(currentHeading) > 160 /*facing cutting wall*/) || (currentX < finishCoordinate && fabs(currentHeading) < 20/*facing table*/)){
        //drive to the left
        driveAuto(8);
        if(currentX < finishCoordinate){
          break;
        }
      }else{
        // drive to the right
        driveAuto(9);
        if(currentX > finishCoordinate){
          break;
        }
      }
    }
  }

  pause();
  Brain.Screen.printAt(0,170, "2currentX  %f", currentX-1500);
  Brain.Screen.printAt(0,190, "2currentY %f", currentY-1500);
}

/******************************************GO TO******************************************/

void goTo( float dest_x, float dest_y, float dest_heading ) {   

  snailTo(dest_heading);

  float start_x, start_y, start_heading, current_x, current_y, current_heading;
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );
  start_heading = local_map.pos.az*180/M_PI;
  start_x = local_map.pos.x;
  start_y = local_map.pos.y;
  


  // convert units to inches and degrees
  start_x /= 25.4;
  start_y /= 25.4;
  start_heading += 180;

  float change_x = dest_x - start_x;
  float change_y = dest_y - start_y;
  Brain.Screen.printAt(10, 20, "%.3f %.3f", change_x, change_y);

  int driveToAngle = (int)(90 - atan((double)change_y/(double)change_x)*180/M_PI)%360;

  // Adjusts to go to -x direction of field
  if ((change_x*change_y > 0 && change_y <0) || (change_x*change_y < 0 && change_y > 0) || (change_x < 0 && change_y == 0)) driveToAngle += 180;

  current_x = start_x, current_y = start_y, current_heading = start_heading;
  driveAngleAbs(driveToAngle, 30);
  dest_x *= 25.4, dest_y *= 25.4;
  while(abs((int)current_x - (int)dest_x) > 50){
    static MAP_RECORD  local_map;
    jetson_comms.get_data( &local_map );
    start_heading = local_map.pos.az*180/M_PI;
    start_x = local_map.pos.x;
    start_y = local_map.pos.y;
  } //link.get_local_location(current_x, current_y, current_heading);
  robotDrive.stop();

  if (abs((int)current_y - (int)dest_y) > 50) {
    int directionY = (current_y - dest_y) ? 0 : 1;

    driveAngleAbs(180*directionY, 30);
    while(abs((int)current_y - (int)dest_y) > 50){
    static MAP_RECORD  local_map;
    jetson_comms.get_data( &local_map );
    start_heading = local_map.pos.az*180/M_PI;
    start_x = local_map.pos.x;
    start_y = local_map.pos.y;
    } //link.get_local_location(current_x, current_y, current_heading);
    robotDrive.stop();
  }

  snailTo(dest_heading);
}