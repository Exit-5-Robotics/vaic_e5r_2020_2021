#include "vex.h"
#include <vex_distance.h>
// call descore() to check if descoring is necessary / descore

bool checkDescore(){
  static MAP_RECORD  local_map;

  jetson_comms.get_data( &local_map );

  int ballCount = 0;
  for(int i = 0; i < local_map.boxnum; i++){
    static MAP_RECORD  local_map;
    jetson_comms.get_data( &local_map );

    if(local_map.boxobj[i].classID != 2){
      ballCount++;
    }
  }

  if(ballCount >= 3){
    int smallestHeight[] = {local_map.boxobj[0].y, 0};
    for(int i = 1; i < local_map.boxnum; i++){
      jetson_comms.get_data( &local_map );

      if(local_map.boxobj[i].y < smallestHeight[0] && local_map.boxobj[i].classID != 2){
        smallestHeight[0] = local_map.boxobj[i].y;
        smallestHeight[1] = i;
      }
    }
    if(local_map.boxobj[smallestHeight[1]].classID != OUR_COLOR){
      return true;
    }
  }
  return false;
}

//POOP function out of a tower
/*void poopTower(int speed){
  pooper.spin(forward, 100, percent);
  wait(2, seconds);
  //Brain.Screen.printAt(10, 220, "reflectivity: %d", ballChecker.reflectivity());
  while(ballChecker.reflectivity() > 230){
    pooper.spin(forward, speed, pct);
  }
  intake.stop();
  wait(2, seconds);
  roller.stop();
}*/

//POOP function just from the ground
void poop(int speed){
  bothRollers.setVelocity(100, pct);
  bothRollers.spinFor(forward, 1, seconds);
  storer.spinFor(1, seconds);
}

void poopEverything(){
  getBall();
  intakeArms.setVelocity(90, pct);
  bothRollers.setVelocity(100, pct);
  intakeArms.spin(forward);
  bothRollers.spin(forward);
  wait(4.3, seconds);
  intakeArms.stop();
  bothRollers.stop();
}

//-------------------------- SCORING THE TWOERS ----------------------------

void score(){ //unshelves ball & scores
  shelf.setVelocity(60, pct);
  roller.setVelocity(100, pct);
  storer.setVelocity(100, pct);
  intakeArms.setVelocity(100, pct);

  shelf.spinFor(reverse, 0.3, seconds);
  roller.spin(reverse);
  storer.spinFor(forward, 0.5, seconds);
  intakeArms.spin(reverse);
  wait(2, seconds);
  intakeArms.stop();
  roller.stop();
}

void store(){
  roller.setVelocity(100, pct);
  storer.setVelocity(100, pct);
  roller.spin(forward);
  storer.spinFor(reverse, 1, seconds);
  roller.stop();
  shelf.setVelocity(60, pct);
  shelf.spinFor(90, degrees);
  shelf.stop(hold);
}

void getBall(){
  pooper.setVelocity(100, pct);
  while(ballChecker.value(pct) > 65){
    pooper.spin(forward);
  }
  pooper.stop();
}

void scoreTower(int whichBall){// 1: our color is bottom/first to intake ball, 2: our color is middle/sendond to intake ball
  getBall();
  if(whichBall == 1){
    store();
  } else {
    //get rid of first ball
    poop(100);
    //get second ball
    getBall();
    //store second ball
    store();
  }
  poopEverything();
  score();
}

void driveToTower(){
  driveAuto(1);
  setSpeed(40);
  intakeArms.setVelocity(70, pct);
  intakeArms.spin(fwd);
  while(!goal.pressing()){}
  intakeArms.stop();
  pause();
}

void descoreTower(int towerNum){
  //if(checkDescore()){

    switch(towerNum){
      case 0:
      turnTo(220);
      driveToTower();
      driveAutoDist(0, 720, 50);
      turnTo(270);
      driveAutoDist(7, 700, 50);
      toStartingPoint(9, 270);
      break;
      
      case 1:
      driveToTower();
      driveAutoDist(0, 200, 10); pause();
      driveAutoDist(8, 200, 10); pause();
      toStartingPoint(9, 270);
      break;
      
      case 2:
      turnTo(330);
      driveToTower();
      driveAutoDist(0, 720, 50);
      turnTo(270);
      driveAutoDist(4, 700, 50);
      toStartingPoint(8, 270);
      break;
      
      case 3:
      break;
      
      case 4:
      break;
      
      case 5:
      turnTo(33);
      driveToTower();
      driveAutoDist(0, 720, 50);
      turnTo(90);
      driveAutoDist(7, 700, 50);
      toStartingPoint(9, 90);
      break;
      
      case 6:
      driveToTower();
      driveAutoDist(0, 200, 10); pause();
      driveAutoDist(8, 200, 10); pause();
      toStartingPoint(9, 90);
      break;
      
      case 7:
      turnTo(150);
      driveToTower();
      driveAutoDist(0, 720, 50);
      turnTo(90);
      driveAutoDist(4, 700, 50);
      toStartingPoint(8, 90);
      break;
      
      case 8:
      break;
      
    }

  
  //}
}