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


void descore (){
  if(checkDescore()){

    static MAP_RECORD  local_map;
    jetson_comms.get_data( &local_map );

    
    //int axisTarget = 1300;

    //find location & go
    //on y-axis or x-axis
    while(local_map.boxnum > 1){
      driveAuto(1);
      Brain.Screen.printAt( 200, 205, "YES");
    }
    Brain.Screen.printAt( 200, 205, "NO");
    pause();

    /*
    int acceptedDeviation = 200;
    if(abs(local_map.pos.x) < acceptedDeviation || abs(local_map.pos.y) < acceptedDeviation){
      //on y-axis or x-axis
      while(local_map.boxnum > 1){
        driveAuto(0);
      }
      driveAutoDist(0, 100);

    } else{
      //on corner

    }
    */


  }
}