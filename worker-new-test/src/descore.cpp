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
void poopTower(int speed){
  pooper.spin(forward, 100, percent);
  wait(2, seconds);
  //Brain.Screen.printAt(10, 220, "reflectivity: %d", ballChecker.reflectivity());
  while(ballChecker.reflectivity() > 230){
    pooper.spin(forward, speed, pct);
  }
  intake.stop();
  wait(2, seconds);
  roller.stop();
}

//POOP function just from the ground
void poop(int speed){
  /*setSpeed(8);
  while(ballChecker.value(analogUnits::mV) < 3200){
    pooper.spin(forward, speed, pct);
    driveAuto(1);
  }
  while(ballChecker.value(analogUnits::mV) > 3200){
    pooper.spin(forward, speed, pct);
    driveAuto(1);
  }
  pooper.stop();
  pause();*/
}

void driveToTower(){
  driveAuto(1);
  setSpeed(20);
  while(!goal.pressing()){}
  pause();
  poopTower(100);
}

void descoreTower(int towerNum){
  //if(checkDescore()){
    if(towerNum == 1 || towerNum == 6){ //just go foward
      driveToTower();
      driveAutoDist(0, 200, 10); pause();
      driveAutoDist(8, 200, 10); pause();
      toStartingPoint();
    } else if (towerNum == 4 || towerNum == 7){ //turn right & go foward

    } else if (towerNum == 0 || towerNum == 5){ //turn left & go foward

    } else if (towerNum == 3){ //turn from tower 1 or 6 & descore

    } else { // 8 or 4, not sure how we're getting there yet

    }
  //}
}