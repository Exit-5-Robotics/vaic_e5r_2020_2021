#include "vex.h"
#include <vex_distance.h>


//TOWER FIXING LOGIC
bool storingBall = true;

void fixWithoutBall(int location){ // location of our color ball in tower that will be scored 0: bottom, 1:middle, 2:top
  int ballsPooped = 0;
  while(ballsPooped < location){
    intake();
    poop();
  }
  intake();
  score();
}

void fixTower(){
  //if(checkDescore()){
      if(storingBall){
        thread scoring(score);
        intake();
    } else {
      fixWithoutBall(5);
    }
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