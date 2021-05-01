#include "vex.h"
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
  //driveAutoDist(0, 45);
  setSpeed(4);
  while(ballChecker.value(analogUnits::mV) < 3200){
    pooper.spin(forward, speed, pct);
    driveAuto(0);
  }
  while(ballChecker.value(analogUnits::mV) > 3200){
    pooper.spin(forward, speed, pct);
    driveAuto(0);
  }
  pooper.stop();
}

//POOP function just from the ground
void poop(int speed){
  setSpeed(8);
  while(ballChecker.value(analogUnits::mV) < 3200){
    pooper.spin(forward, speed, pct);
    driveAuto(1);
  }
  while(ballChecker.value(analogUnits::mV) > 3200){
    pooper.spin(forward, speed, pct);
    driveAuto(1);
  }
  pooper.stop();
  pause();
}

void descore (float desired_heading){
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  if(checkDescore()){

    int ballCount = 0;
    for(int i = 0; i < local_map.boxnum; i++){
      jetson_comms.get_data( &local_map );

      if(local_map.boxobj[i].classID != 2){
        ballCount++;
      }
    }
    

    while(!goal.pressing()){
      jetson_comms.get_data( &local_map );
      for(int i = 0; i < local_map.boxnum; i++){
      jetson_comms.get_data( &local_map );

      if(local_map.boxobj[i].classID != 2){
        ballCount++;
      }
    }

      driveAuto(1);
      if(ballCount<3){
        pooper.spin(forward, 80, pct);
      }
    }
    pause();

    poopTower(100);

    //go back to node position
    //snailTo(desired_heading);
    setSpeed(40);
    driveAutoDist(0, 200);
    pooper.setVelocity(5, pct);
    pooper.spinFor(reverse, 100, deg);
    while(!backStopper.pressing()){
      //pooper.spin(reverse, 80, pct);
      driveAuto(0);
    }
    //snailTo(desired_heading);
    pooper.spinFor(forward, 100, deg);
    driveAutoDist(1, 180);
    

    //update manager to new tower inventory

  }
}