#include "vex.h"
#include <cmath>
#include <vex_imu.h>
#include <iostream>
using namespace vex;

const int intakeDriveSpeed = 10;
int distPosition = 1;


/*
TO DO: 
- 
*/
double lineColorR;
double lineColorL;

void reset(){
  tilt.calibrate();
  while(tilt.isCalibrating()){}
  rightLine.setLightPower(100, percent);
  leftLine.setLightPower(100, percent);
  rightLine.setLight(ledState::on);
  leftLine.setLight(ledState::on);
  this_thread::sleep_for(1000);
  lineColorR = leftLine.brightness(true) *2.5; //~6500
  lineColorL = rightLine.brightness(true) *2.5; //~6500
  Brain.Screen.printAt(10, 20, "lineColorR: %f", lineColorR);
  Brain.Screen.printAt(10, 40, "lineColorL: %f", lineColorL);
}

double angleDifference(int target, int dir){
  if( (dir == 2 && target < tilt.heading()) || (dir == 3 && target > tilt.heading()) ){
    return fabs(target + tilt.heading() - 360);
  }
  return fabs(target - tilt.heading());
}

void turnTo(int targetAngle){
  int turningDirection;
  if((fabs(targetAngle - tilt.heading()) < 180 && tilt.heading() < targetAngle) || (fabs(targetAngle - tilt.heading()) > 180 && tilt.heading() > targetAngle)){ //CW
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
    if ( (turningDirection == 3 && ((targetAngle > tilt.heading() && fabs(targetAngle - tilt.heading()) >= 180) ||  (targetAngle < tilt.heading() && fabs(targetAngle - tilt.heading()) < 180))) || (turningDirection == 2 && ((targetAngle < tilt.heading() && fabs(targetAngle - tilt.heading()) >= 180 ) || (targetAngle > tilt.heading() && fabs(targetAngle - tilt.heading()) < 180))) ) {
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
  driveAutoDist(0, 800, 20);
}

void toStartingPoint(int from, int endDir){ //8: approaching from right, 9: approaching from left
  bool fastCheck = false;
  bool firstLine = false;
  bool secondLine = false;
  bool done = false;

  driveAuto(from);
  setSpeed(10);

  while (!fastCheck){
    if((from == 8 && rightLine.brightness(true) > lineColorR)){
      fastCheck = true;
      from = 9;
      driveAuto(9);
    } else if ((from == 9 && leftLine.brightness(true) > lineColorL)){
      fastCheck = true;
      from = 8;
      driveAuto(8);
    }
  }
  Brain.Screen.printAt(10, 100, "fastLine finished");
  /*
  setSpeed(8);

  while(!done){
     
    if(rightLine.brightness() > lineColorR && from == 9){
      //Brain.Screen.printAt(10, 100, "firstLine 9");
      firstLine = true;
    }
    if(firstLine && leftLine.brightness() > lineColorL && from == 9){
      //Brain.Screen.printAt(10, 120, "secondLine 9");
      secondLine = true;
      pause();
    }
    //from 8
    if(leftLine.brightness() > lineColorL && from == 8){
      //Brain.Screen.printAt(10, 100, "firstLine 8");
      firstLine = true;
    }
    if(firstLine && rightLine.brightness() > lineColorR && from == 8){
      //Brain.Screen.printAt(10, 120, "secondLine 8");
      secondLine = true;
      pause();
    }
    //double check
    if(secondLine && rightLine.brightness() > lineColorR){
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
    
  }*/
  //turnTo(endDir);
  pause();
  //toBestY();
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

void intake() {
  pause();
  intakeWheels.spinFor(fwd, 800, degrees, 60, vex::velocityUnits::pct);
  Brain.Screen.printAt(10, 120, "starting");
  while (ballThree.value(analogUnits::mV) > 3300) {}
  pause();
  Brain.Screen.printAt(10, 140, "done");
  intakeWheels.spinFor(fwd, 800, degrees, 60, vex::velocityUnits::pct);
  intakeWheels.stop();
}

void intakeNoDrive() {
  while (ballThree.value(analogUnits::mV) > 3300) {
    intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  }
  intakeWheels.stop();
}

int score() {
  scoringRollers.setVelocity(100, percentUnits::pct);
  scoringRollers.spinFor(fwd, 0.4, seconds);
  topRoller.spinFor(fwd, 1, seconds);
  return 0;
}

void poop() {
  // run if the ball is in adjustHold position
  //intake(intakeDriveSpeed);
  botRoller.spinFor(fwd, 150, vex::rotationUnits::deg, 100, vex::velocityUnits::pct, false);
  topRoller.spinFor(reverse, 300, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}

int adjustHold(void) {
  botRoller.setVelocity(100, pct);
  botRoller.spinFor(fwd, 0.8, seconds);
  return 0;
}

void adjustWIntake(){
  intakeRollers.setVelocity(100, pct);
  intakeRollers.spinFor(0.8, seconds);
}