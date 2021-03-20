#include "vex.h"
// call descore() to check if descoring is necessary / descore

bool checkDescore(){
  int sum0 = 0, sum1 = 0, sum2 = 0;
  static MAP_RECORD  local_map;

  jetson_comms.get_data( &local_map );

  if(local_map.boxnum >= 3){
    int avgY[local_map.boxnum] = {};
    for(int k = 0; k < local_map.boxnum; k++){
      for(int i = 0; i < 15; i++){
        static MAP_RECORD  local_map;
        avgY[k] += local_map.boxobj[k].y;
      }
      avgY[k] /= 15;
    }
    

    //{y pos, id}
    int highestBox[] = {avgY[0], 0}; 
    for(int i = 1; i < local_map.boxnum; i++){
      if (avgY[i] > highestBox[0]){
        highestBox[0] = avgY[i];
        highestBox[1] = i;
      }
    }    
    
    if(local_map.mapobj[highestBox[1]].classID != OUR_COLOR){
      return true;
    }
  }
  driveAutoDist(1, 1000);
  return false;
}




void descore (){
  if(checkDescore()){
    driveAutoDist(0, 10);
  }
}