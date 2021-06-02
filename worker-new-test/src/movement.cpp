#include "vex.h"
#include <cmath>
#include <vex_imu.h>

using namespace vex;

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
  lineColorR = tileColorR *0.6; //~6500
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
  if((fabs(targetAngle - getHeading()) < 180 && getHeading() < targetAngle) || (fabs(targetAngle - getHeading()) > 180 && getHeading() > targetAngle)){ //CW
    driveAuto(2);
  } else { //CCW
    driveAuto(3);
  }
  setSpeed(5);
  while(fabs(targetAngle - getHeading()) > 2){}
  pause();
}

void PIDTurnTo(int targetAngle){
  if((fabs(targetAngle - getHeading()) < 180 && getHeading() < targetAngle) || (fabs(targetAngle - getHeading()) > 180 && getHeading() > targetAngle)){ //CW
    driveAuto(2);
  } else { //CCW
    driveAuto(3);
  }

  double Kp = 0.05;
  double Ki = 0.04;
  double Kd = 0.1;

  double error = targetAngle - getHeading();
  double errorSum = 0;
  double previousError = error;
  double errorChange;

  while(fabs(targetAngle - getHeading()) > 0.5){
    error = targetAngle - getHeading();
    errorSum += error;
    errorChange = error - previousError;
    previousError = error;

    setSpeed( (error*Kp) + (errorSum*Ki) + (errorChange * Kd));
  }

}

void toBestY(){
  while(!backStopper.pressing()){
    driveAuto(0);
    setSpeed(10);
  }
  pause();
  driveAutoDist(1, 420, 10);
}

void toStartingPoint(int from){ //8: approaching from right, 8: approaching from left
  bool firstLine = false;
  bool secondLine = false;
  bool timeToStop = false;

  //pause();
  driveAuto(from);
  setSpeed(20);
  
  while(!timeToStop){
    if(fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 9){
      Brain.Screen.printAt(10, 100, "firstLine");
      firstLine = true;
      setSpeed(5);
    }
    if(firstLine && fabs(leftLine.value(percentUnits::pct) - lineColorL) < 10 && from == 9){
      Brain.Screen.printAt(10, 120, "secondLine");
      secondLine = true;
      pause();
      driveAuto(8);
      setSpeed(5);
    }
    if(secondLine && fabs(rightLine.value(percentUnits::pct) - lineColorR) < 10 && from == 9){
      Brain.Screen.printAt(10, 140, "timeToStop");
      timeToStop = true;
      pause();
    }
    //from 8
    if(fabs(leftLine.value(percentUnits::pct) - lineColorR) < 10 && from == 8){
      Brain.Screen.printAt(10, 100, "firstLine");
      firstLine = true;
      pause();
      wait(0.5, seconds);
      driveAuto(8);
      setSpeed(5);
    }
    if(firstLine && fabs(rightLine.value(percentUnits::pct) - lineColorL) < 10 && from == 8){
      Brain.Screen.printAt(10, 120, "secondLine");
      secondLine = true;
      pause();
      driveAuto(9);
      setSpeed(5);
    }
    if(secondLine && fabs(leftLine.value(percentUnits::pct) - lineColorR) < 10 && from == 8){
      Brain.Screen.printAt(10, 140, "timeToStop");
      timeToStop = true;
      pause();
    }
  }
  turnTo(270);
  pause();
  toBestY();
}

void alignTower1(){
  //if its a check, currentTower = 0, so just do little wigglies
  //have different situations for if current tower = 2||3 to realign w/center
}

void alignTower0(){
  //align & check descore, then run alignTower1()
}

void alignTower2(){
  //align & check descore, then run alignTower1()
}

void alignTower3(){
  //twist until facing middle tower, check middle tower & descore if neccessary, then spin again to align with tower1
}

void toOptimalY(){
  //not sure if this is necessary, just turn & use jetston to check currentY to make sure robot is in good Ypos for corner tower checking
  //possibly do this & then alignTower1() before turning to check corner towers
}

void scoutBalls(){
  //using the tower scoring method, if an additinal ball is needed to score, scout around & get a ball after the cycle, then return to tower1 alignment & repeat cycle with new ball
  //OR once we know additinall balls are needed, scout for a ball one at a time, alignTower1 and put the ball in the correct tower, then repeat as many times as necessary to fill tower
}

