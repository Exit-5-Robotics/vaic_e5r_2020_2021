#include "vex.h"
// call descore() to check if descoring is necessary / descore

bool checkDescore(){
  static MAP_RECORD  local_map;

  jetson_comms.get_data( &local_map );

  if(local_map.boxnum >= 3){
    int largestAvgY[] = {0, 0}; // {avg, boxnum}
    for(int k = 0; k < local_map.boxnum; k++){
      int currentAvgY = 0;
      for(int i = 0; i < 15; i++){
        static MAP_RECORD  local_map;
        jetson_comms.get_data( &local_map );
        currentAvgY += local_map.boxobj[k].y;
      }
      currentAvgY /= 15;
      if(currentAvgY > largestAvgY[0]){
        largestAvgY[0] = currentAvgY;
        largestAvgY[1] = k;
      }
    }
    
    if(local_map.mapobj[largestAvgY[1]].classID != OUR_COLOR){
      return true;
    }
  }
  driveAutoDist(1, 1000);
  return false;
}




void descore (){
  if(checkDescore()){

    static MAP_RECORD  local_map;
    jetson_comms.get_data( &local_map );

    int acceptedDeviation = 200;
    //int axisTarget = 1300;

    //find location & go
    if(abs(local_map.pos.x) < acceptedDeviation || abs(local_map.pos.y) < acceptedDeviation){
      //on y-axis or x-axis
      while(local_map.boxnum > 1){
        driveAuto(0);
      }
      driveAutoDist(0, 100);

    } else{
      //on corner

    }


  }
}