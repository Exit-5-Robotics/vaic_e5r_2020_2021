#include "vex.h"
// call descore() to check if descoring is necessary / descore

bool checkDescore(){
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  if(local_map.boxnum >= 3){
    //{y pos, id}
    int highestBox[] = {local_map.boxobj[0].y, 0}; 
    for(int i = 1; i < local_map.boxnum; i++){
      if (local_map.boxobj[i].y > highestBox[0]){
        highestBox[0] = local_map.boxobj[i].y;
        highestBox[1] = i;
      }
    }
    Brain.Screen.printAt( 10, 200, "highestBox    %d", highestBox[1] );

    Brain.Screen.printAt(10, 260, "color    %s", local_map.mapobj[highestBox[1]].classID);
    
    if(local_map.mapobj[highestBox[1]].classID != OUR_COLOR){
        driveAutoDist(0, 300); //move towards tower
      return true;
    }else{
      driveAutoDist(1, 100); //move backwards - can change movement later
    }
  }
  
  return false;
}


void descore (){
  if(checkDescore()){
    
  }
}