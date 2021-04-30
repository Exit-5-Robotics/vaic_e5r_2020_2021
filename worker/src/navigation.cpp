#include "vex.h"
using namespace vex;

/*
To do:
- collect centerNodes[]
- test snailTo()
- test sideGoTo()
- test goTo()
- outline isolation
- get data for isolation
- impliment the matrix stuff
- DONE: change descore so that the robot goes back to node it came from
- change descore so that it updates the matrix after it completes
- test everything
*/

//float centerNodes[] = {/*x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8*/};
float centerNodes[] = {/*x0, x1, y2, y3, x4, x5, y6, y7*/};
float nodeHeadings[] = {180, -135, -90, -45, 0, 45, 90, 135};


void navigateForever(){
  int count;
  if(OUR_COLOR){ //blue
    count = 2;
  } else {
    count = 6;
  }
  while(1){
    count++;
    if(count == 8){
      count = 0;
    }

    if(count % 2 == 0){
      snailTo(nodeHeadings[count]);
    }
    sideGoTo(centerNodes[count]);
    snailTo(nodeHeadings[count]);

    descore(nodeHeadings[count]);
  }
}

