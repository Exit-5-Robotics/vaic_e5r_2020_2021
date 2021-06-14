#include "vex.h"
#include <vex_distance.h>


//TOWER FIXING LOGIC
bool haveBall = true;

void sortBalls(){
  bool foundBall = false;
  int ballsSorted = 0;
  while(ballsSorted < 3 && !foundBall){
    adjustWIntake();
    this_thread::sleep_for(2000);
    //seeing if that ball is our color
    if( (OUR_COLOR && colorSensor.color().rgb()/10000000 !=1) || (!OUR_COLOR && colorSensor.color().rgb()/10000000 ==1 )){ // we found our color ball, store it
      foundBall = true;
      Brain.Screen.printAt(10, 100, "color: %d", colorSensor.color().rgb()/10000000);
      scoringRollers.setVelocity(100, pct);
      scoringRollers.spinFor(0.15, seconds);
      topRoller.spin(fwd);
      while(ballZero.value(pct) > 64){Brain.Screen.printAt(10, 140, "hit top");}
      //Brain.Screen.printAt(10, 140, "stopValue: %d", ballZero.value(pct));
      topRoller.stop();
      topRoller.setBrake(hold);
    } else{ //not our color, poop it
      poop();
    }
    ballsSorted++; 
  }
  this_thread::sleep_for(2000);
  //empty any leftovers
  intakeRollers.setVelocity(100, percent);
  intakeRollers.spin(fwd);
  topRoller.setBrake(hold);
  this_thread::sleep_for(2500);
  intakeRollers.stop();
}

void fixTower(){
  //if(checkDescore()){
    thread scoring(score);
    intake();
    if(!haveBall){

    }
    thread sort(sortBalls);
  //}
}


//DESCORE LOGIC
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

//MORE LIKE NAV BUT ITS FINEEEEEE

void driveToTower(){
  driveAuto(1);
  setSpeed(50);
  intakeWheels.spin(fwd, 100, vex::velocityUnits::pct);
  thread adjust(adjustHold);
  while(!goal.pressing()){}
  pause();
  Brain.Screen.printAt(10, 100, "intake");
  fixTower();
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