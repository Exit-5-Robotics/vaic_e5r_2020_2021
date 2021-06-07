#include "vex.h"
#include <cmath>
#include <vex_imu.h>
#include <iostream>
using namespace vex;

const int rollerDistance = 400;
const int intakeDriveSpeed = 10;
int distPosition = 1;


/*
TO DO: 
- 
*/
double tileColorR;
double tileColorL;
double lineColorR;
double lineColorL;

void reset(){
  this_thread::sleep_for(1000);
  tilt.calibrate();
  while(tilt.isCalibrating()){}
  tileColorL = leftLine.value(percentUnits::pct); //~2,750
  tileColorR = rightLine.value(percentUnits::pct); //~3,000
  lineColorR = tileColorR *0.75; //~6500
  lineColorL = tileColorL *0.75; //~6500
  tilt.resetHeading();
  Brain.Screen.printAt(10, 20, "lineColorR: %f", lineColorR);
  Brain.Screen.printAt(10, 40, "lineColorL: %f", lineColorL);
}

double getHeading(){
  if(!OUR_COLOR){ // if red, shift 180 degrees
    if(tilt.heading() < 180){
      return tilt.heading() + 180;
    } else {
      return tilt.heading() - 180;
    }
  } return tilt.heading();
}

double angleDifference(int target, int dir){
  if( (dir == 2 && target < getHeading()) || (dir == 3 && target > getHeading()) ){
    return fabs(target + getHeading() - 360);
  }
  return fabs(target - getHeading());
}

void turnTo(int targetAngle){
  int turningDirection;
  if((fabs(targetAngle - getHeading()) < 180 && getHeading() < targetAngle) || (fabs(targetAngle - getHeading()) > 180 && getHeading() > targetAngle)){ //CW
    driveAuto(2);
    turningDirection = 2;
  } else { //CCW
    driveAuto(3);
    turningDirection = 3;
  }

  double Kp = 0.7;
  double Ki = 0.002;
  double Kd = 0.08;

  double error;
  double errorSum = 0;
  double previousError = 0;
  double errorChange;

  if(angleDifference(targetAngle, turningDirection) < 8){
    Kp = 2;
  }

  while(angleDifference(targetAngle, turningDirection) > 0.5){
    //finding error
    error = -1 * angleDifference(targetAngle, turningDirection);
    if ( (turningDirection == 3 && ((targetAngle > getHeading() && fabs(targetAngle - getHeading()) >= 180) ||  (targetAngle < getHeading() && fabs(targetAngle - getHeading()) < 180))) || (turningDirection == 2 && ((targetAngle < getHeading() && fabs(targetAngle - getHeading()) >= 180 ) || (targetAngle > getHeading() && fabs(targetAngle - getHeading()) < 180))) ) {
      error *= -1;
    }
    
    errorSum += error;
    errorChange = error - previousError;
    previousError = error;

    setSpeed( (error*Kp) + (errorSum*Ki) + (errorChange * Kd));
    this_thread::sleep_for(20);  
  }
  Brain.Screen.printAt(10, 100, "done turning");
  setSpeed(50);
  //Brain.Screen.printAt(10, 100, "Error: %f", error*Kp); Brain.Screen.printAt(10, 120, "ErrorSum: %f", errorSum*Ki); Brain.Screen.printAt(10, 140, "ErrorChange: %f", errorChange*Kd);  
  pause();

}

void toBestY(){
  while(!goal.pressing()){
    driveAuto(1);
    setSpeed(20);
  }
  pause();
  driveAutoDist(0, 600, 20);
}

void toStartingPoint(int from, int endDir){ //8: approaching from right, 9: approaching from left
  bool firstLine = false;
  bool secondLine = false;
  bool done = false;

  driveAuto(from);
  setSpeed(20);

  while(!done){
     
    if(fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 9){
      //Brain.Screen.printAt(10, 100, "firstLine 9");
      firstLine = true;
      setSpeed(5);
    }
    if(firstLine && fabs(leftLine.value(percentUnits::pct) - lineColorL) < 10 && from == 9){
      //Brain.Screen.printAt(10, 120, "secondLine 9");
      secondLine = true;
      pause();
    }
    //from 8
    if(fabs(leftLine.value(percentUnits::pct) - lineColorL) < 10 && from == 8){
      //Brain.Screen.printAt(10, 100, "firstLine 8");
      firstLine = true;
      setSpeed(5);
    }
    if(firstLine && fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 8){
      //Brain.Screen.printAt(10, 120, "secondLine 8");
      secondLine = true;
      pause();
    }
    //double check
    if(secondLine && fabs(rightLine.value(percentUnits::pct) - lineColorR) > 10){
      firstLine = false;
      secondLine = false;
      setSpeed(20);
      if (from == 8){
        driveAutoDist(8, 100, 20);
        driveAuto(9);
        from = 9;
      } else{
        driveAutoDist(9, 100, 20);
        driveAuto(8);
        from = 8;
      }
      setSpeed(5);
    } else if (secondLine){
      done = true;
    }
    
  }
  turnTo(endDir);
  pause();
  toBestY();
}

void toFlipLine(){
  driveAuto(9); setSpeed(50); pause();
  driveAutoDist(9, 700, 50);
  pause();
  turnTo(0);
  driveAutoDist(9, 1600, 50);
  pause();
  turnTo(90);
  pause();
  Brain.Screen.printAt( 10, 90, "Status: toStartingPoint");
  toStartingPoint(9, 90);
}

void scoutBalls(){
  //using the tower scoring method, if an additinal ball is needed to score, scout around & get a ball after the cycle, then return to tower1 alignment & repeat cycle with new ball
  //OR once we know additinall balls are needed, scout for a ball one at a time, alignTower1 and put the ball in the correct tower, then repeat as many times as necessary to fill tower
}




/////////////////////////////////////////BALL HANDLING//////////////////////////////

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

int adjustHold() {
  while (ballZero.value(analogUnits::mV) > 3400) {
    botRoller.spin(fwd, 100, vex::velocityUnits::pct);
    topRoller.spin(fwd, 100, vex::velocityUnits::pct);
  }
  botRoller.stop();
  topRoller.stop();
  return 0;
}