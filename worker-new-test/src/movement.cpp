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

void turnTo(int targetAngle){
  int turningDirection;
  if((fabs(targetAngle - getHeading()) < 180 && getHeading() < targetAngle) || (fabs(targetAngle - getHeading()) > 180 && getHeading() > targetAngle)){ //CW
    driveAuto(2);
    turningDirection = 2;
  } else { //CCW
    driveAuto(3);
    turningDirection = 3;
  }

  double Kp = 0.8;
  double Ki = 0.0008;
  double Kd = 0.08;

  double error;
  double errorSum = 0;
  double previousError = 0;
  double errorChange;

  while(fabs(targetAngle - getHeading()) > 0.5){
    //finding error
    error = -1 * fabs(targetAngle - getHeading());
    if ( (turningDirection == 3 && ((targetAngle > getHeading() && fabs(targetAngle - getHeading()) >= 180) ||  (targetAngle < getHeading() && fabs(targetAngle - getHeading()) < 180))) || (turningDirection == 2 && ((targetAngle < getHeading() && fabs(targetAngle - getHeading()) >= 180 ) || (targetAngle > getHeading() && fabs(targetAngle - getHeading()) < 180))) ) {
      error *= -1;
    }

    
    errorSum += error;
    errorChange = error - previousError;
    previousError = error;

    setSpeed( (error*Kp) + (errorSum*Ki) + (errorChange * Kd));
    this_thread::sleep_for(20);  
  }
  //Brain.Screen.printAt(10, 100, "Error: %f", error*Kp); Brain.Screen.printAt(10, 120, "ErrorSum: %f", errorSum*Ki); Brain.Screen.printAt(10, 140, "ErrorChange: %f", errorChange*Kd);  
  pause();

}

void toBestY(){
  while(!backStopper.pressing()){
    driveAuto(0);
    setSpeed(10);
  }
  pause();
  driveAutoDist(1, 420, 10);
}

void toStartingPoint(int from){ //8: approaching from right, 9: approaching from left
  bool firstLine = false;
  bool secondLine = false;
  //bool timeToStop = false;

  //pause();
  driveAuto(from);
  setSpeed(10);

  while(!secondLine){
     
    if(fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 9){
      Brain.Screen.printAt(10, 100, "firstLine 9");
      firstLine = true;
      setSpeed(5);
    }
    if(firstLine && fabs(leftLine.value(percentUnits::pct) - lineColorL) < 10 && from == 9){
      Brain.Screen.printAt(10, 120, "secondLine 9");
      secondLine = true;
      pause();
      driveAuto(8);
      setSpeed(5);
    }/*
    if(secondLine && fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 9){
      Brain.Screen.printAt(10, 140, "timeToStop 9");
      timeToStop = true;
      pause();
    }*/
    //from 8
    if(fabs(leftLine.value(percentUnits::pct) - lineColorL) < 10 && from == 8){
      Brain.Screen.printAt(10, 100, "firstLine 8");
      firstLine = true;
      setSpeed(5);
    }
    if(firstLine && fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 8){
      Brain.Screen.printAt(10, 120, "secondLine 8");
      secondLine = true;
      pause();
      driveAuto(9);
      setSpeed(5);
    }/*
    if(secondLine && fabs(leftLine.value(percentUnits::pct) - lineColorL) < 10 && from == 8){
      Brain.Screen.printAt(10, 140, "timeToStop 8");
      timeToStop = true;
      pause();
    }*/
  }
  //turnTo(270);
  pause();
  //toBestY();
}

void toFlipLine(){
  driveAutoDist(9, 400, 30);
  turnTo(0);
  driveAutoDist(9, 800, 30);
  turnTo(90);
  toStartingPoint(9);
}

void scoutBalls(){
  //using the tower scoring method, if an additinal ball is needed to score, scout around & get a ball after the cycle, then return to tower1 alignment & repeat cycle with new ball
  //OR once we know additinall balls are needed, scout for a ball one at a time, alignTower1 and put the ball in the correct tower, then repeat as many times as necessary to fill tower
}

