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
      static MAP_RECORD  local_map;
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

void poop(int speed){
  while(ballChecker.value(analogUnits::mV) < 3200){
    pooper.spin(forward, speed, pct);
  }
  while(ballChecker.value(analogUnits::mV) > 3200){
    pooper.spin(forward, speed, pct);
  }
  pooper.stop();
}


void descore (){
  if(checkDescore()){

    while(!goal.pressing()){
      driveAuto(1);
    }
    pause();

    poop(100);

  }
}