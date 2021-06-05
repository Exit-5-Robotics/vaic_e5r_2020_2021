#include "vex.h"
#include <cmath>
#include <vex_imu.h>
#include <iostream>
using namespace vex;

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
  lineColorR = tileColorR *0.7; //~6500
  lineColorL = tileColorL *0.5; //~6500
  tilt.resetHeading();
  Brain.Screen.printAt(10, 20, "lineColorR: %f", lineColorR);
  Brain.Screen.printAt(10, 40, "lineColorL: %f", lineColorL);
}

double getHeading(){
  if(!OUR_COLOR){ // if red, shift 180 degrees
    if(tilt.heading() < 180){
      return tilt.heading() + 180;
    } else {
      return 180 - tilt.heading();
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
  while(!backStopper.pressing()){
    driveAuto(0);
    setSpeed(20);
  }
  pause();
  driveAutoDist(1, 420, 10);
}

void toStartingPoint(int from, int endDir){ //8: approaching from right, 9: approaching from left
  bool firstLine = false;
  bool secondLine = false;
  bool done = false;

  driveAuto(from);
  setSpeed(10);

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

