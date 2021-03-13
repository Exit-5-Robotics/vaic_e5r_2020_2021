#include "vex.h"
// call descore() to check if descoring is necessary / descore

bool checkDescore(){
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  if(local_map.boxnum >= 3){
    while(1){
        driveAuto(3);
    }
    //{y pos, id}
    int highestBox[] = {local_map.boxobj[0].y, 0}; 
    for(int i = 1; i < local_map.boxnum; i++){
      if (local_map.boxobj[i].y > highestBox[0]){
        highestBox[0] = local_map.boxobj[i].y;
        highestBox[1] = i;
      }
    }
    
    if(local_map.mapobj[highestBox[1]].classID != OUR_COLOR){
      return true;
    }
  }
  
  return false;
}


void descore (){
  if(checkDescore()){
    
  }
}