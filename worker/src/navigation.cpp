#include "vex.h"
using namespace vex;

float order[] = {3, 4, 0, 6, 1, 7, 2, 5}; //automatically red

float centerNodes[] = {/*x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8*/};

void setStart(int color){
  if(color){ //blue
    order[0] = 1;
    order[1] = 7;
    order[2] = 2;
    order[3] = 5;
    order[4] = 3;
    order[5] = 4;
    order[6] = 0;
    order[7] = 6;
  }

}

void checkTower(){
  /*
    1. check info for tower in front
    2. if the top is not our color:
        a. descore
        b. return to center position
    3. send updated matrix info to manager
  */
}

void navigateForever(){
  int count = 0;
  while(1){
    if(count > 7){
      count = 0;
    }
    checkTower();
    //goTo(centerNodes[order[count*2]], centerNodes[order[count*2 + 1]], 5); // also turns 45 degrees
    count++;
  }
}

