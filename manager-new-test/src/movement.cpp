#include "vex.h"
#include <cmath>
#include <vex_imu.h>
#include <iostream> 
using namespace vex;

const int intakeDriveSpeed = 80;
int distPosition = 1;

int getIntakeSpeed(){
  return intakeDriveSpeed;
}

/*
TO DO: 
- 
*/
double lineColorR;
double lineColorL;

double getLineColor(char which){
  if (which == 'R'){
    return lineColorR;
  } return lineColorL;
}

void reset(){
  tilt.calibrate();
  while(tilt.isCalibrating()){}
  tilt.setHeading(0, vex::rotationUnits::deg);
  rightLine.setLightPower(100, percent);
  leftLine.setLightPower(100, percent);
  rightLine.setLight(ledState::on);
  leftLine.setLight(ledState::on);
  this_thread::sleep_for(1000);
  //lineColorR = leftLine.brightness(true) * 3 ; //~6500
  lineColorR = 0.25; //~6500
  // lineColorL = rightLine.brightness(true) * 3; //~6500
  lineColorL = 0.22; //~6500
  Brain.Screen.printAt(10, 20, "lineColorR: %f", lineColorR);
  Brain.Screen.printAt(10, 40, "lineColorL: %f", lineColorL);
}

double angleDifference(int target, int dir){
  if( (dir == 2 && target < tilt.heading()) || (dir == 3 && target > tilt.heading()) ){
    if(dir == 3){
      return (360 - target) + tilt.heading();
    } else {
      return (360 - tilt.heading()) + target;
    }
  }
  return fabs(target - tilt.heading());
}

void turnTo(int targetAngle){
  int turningDirection;
  if((fabs(targetAngle - tilt.heading()) < 180 && tilt.heading() < targetAngle) || (fabs(targetAngle - tilt.heading()) > 180 && tilt.heading() > targetAngle)){ //CW
    driveAuto(2);
    turningDirection = 2;
    //Brain.Screen.printAt(10, 140, "driveDir: 2");
    //if((fabs(targetAngle - tilt.heading()) < 180 && tilt.heading() < targetAngle)){}
  } else { //CCW
    driveAuto(3);
    turningDirection = 3;
    //Brain.Screen.printAt(10, 140, "driveDir: 3");
  }

  double Kp = 1.2;
  double Ki = 0.005;
  double Kd = 2;

  double error;
  double errorSum = 0;
  double previousError = 0;
  double errorChange;

  
  if(angleDifference(targetAngle, turningDirection) < 8){
    Kp = 2;
  }
  Brain.Timer.reset();
  while(angleDifference(targetAngle, turningDirection) > 0.5){
    //finding error

    error = angleDifference(targetAngle, turningDirection);
    
    errorSum += error;
    errorChange = error - previousError;
    previousError = error;
    int speed;

    if(fabs(error) < 2){
      speed = 5;
    } else{
      speed = (error*Kp) + /*(errorSum*Ki)*/ + (errorChange * Kd);
    }
    if ( (turningDirection == 3 && ((targetAngle > tilt.heading() && fabs(targetAngle - tilt.heading()) >= 180) ||  (targetAngle < tilt.heading() && fabs(targetAngle - tilt.heading()) < 180))) || (turningDirection == 2 && ((targetAngle < tilt.heading() && fabs(targetAngle - tilt.heading()) >= 180 ) || (targetAngle > tilt.heading() && fabs(targetAngle - tilt.heading()) < 180))) ) {
      setSpeed(-1*speed);
    } else {
      setSpeed(speed);
    }
    this_thread::sleep_for(20);  
    Brain.Screen.printAt(10, 100, "error: %f", error);
    Brain.Screen.printAt(10, 120, "errorChange: %f", errorChange);
  }
  pause();
  Brain.Screen.printAt(10, 140, "done");

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
  pause();
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

void driveToLine(int dir, int speed, int reverseTime, char whichSensor){ //only used when robot is supposed to be perpendicular to the line
  Brain.Timer.reset();
  int driveDirection = dir;
  driveAuto(dir);
  setSpeed(speed);
  while( (rightLine.brightness(true) < getLineColor('R') && whichSensor == 'R') || (leftLine.brightness(true) < getLineColor('L') && whichSensor == 'L') ){
    if(Brain.Timer.time(msec) >= reverseTime){ // in case the line is missed
      if(driveDirection == 1){
        driveDirection = 0;
        driveAuto(0);
      } else if(driveDirection == 0) {
        driveDirection = 1;
        driveAuto(1);
      } else if(driveDirection == 8) {
        driveDirection = 9;
        driveAuto(9);
      }else if(driveDirection == 9) {
        driveDirection = 8;
        driveAuto(8);
      }
      setSpeed(15);
      Brain.Timer.reset();
    }
  }
  robotDrive.stop(hold);
}


/////////////////////////////////////////BALL HANDLING//////////////////////////////

void intake(bool useBot) { //uses only spinny orange wheels to intake many balls
  //driveAuto(1);
  setSpeed(5);
  intakeWheels.setVelocity(intakeDriveSpeed, pct);
  if(useBot){botRoller.spinFor(fwd, 600, degrees, 70, vex::velocityUnits::pct, false);}
  //intakeWheels.spinFor(fwd, 800, degrees, 100, vex::velocityUnits::pct);
  intakeWheels.spin(fwd);
  Brain.Screen.printAt(10, 120, "starting");
  Brain.Timer.reset();
  while (ballThree.value(analogUnits::mV) > 3300 || Brain.Timer.time() > 4000) {}
  Brain.Screen.printAt(10, 140, "done");
  intakeWheels.spinFor(fwd, 600, degrees, intakeDriveSpeed/2, vex::velocityUnits::pct);
  intakeWheels.stop();
  pause();
}

void intakeNoDrive() {
  while (ballThree.value(analogUnits::mV) > 3300) {
    intakeWheels.spin(fwd, intakeDriveSpeed, vex::velocityUnits::pct);
  }
  intakeWheels.stop();
}

int score() {
  scoringRollers.setVelocity(100, percentUnits::pct);
  scoringRollers.spin(fwd);
  while(ballZero.value(pct) > 64){}
  scoringRollers.stop();
  topRoller.spinFor(fwd, 0.8, seconds);
  return 0;
}

void poop() {
  // run if the ball is in adjustHold position
  //intake(intakeDriveSpeed);
  botRoller.spinFor(fwd, 150, vex::rotationUnits::deg, 100, vex::velocityUnits::pct, false);
  topRoller.spinFor(reverse, 300, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
}

int adjustHold() {
  intakeRollers.setVelocity(100, pct);
  botRoller.spin(fwd);
  Brain.Timer.reset();
  while(middleBall.objectDistance(mm) > 70 ){
    if(Brain.Timer.time() > 2000){
      intakeRollers.stop();
      return 0;
    }
  }
  //Brain.Screen.printAt(10, 140, "stopMiddle: %f", middleBall.objectDistance(mm));
  //Brain.Screen.printAt(10, 140, "adjusting");
  intakeRollers.stop();
  return 1;
}

int adjustWIntake(){
  this_thread::sleep_for(500);
  intakeRollers.setVelocity(100, pct);
  intakeRollers.spin(fwd);
  Brain.Timer.reset();
  while(middleBall.objectDistance(mm) > 70 ){
    if(Brain.Timer.time() > 2000){
      intakeRollers.stop();
      return 0;
    }
  }
  //Brain.Screen.printAt(10, 140, "stopMiddle: %f", middleBall.objectDistance(mm));
  //Brain.Screen.printAt(10, 140, "adjusting");
  intakeRollers.stop();
  return 1;
}

int getRed(){
  int redAmt = colorSensor.color().rgb();
  return redAmt;
}