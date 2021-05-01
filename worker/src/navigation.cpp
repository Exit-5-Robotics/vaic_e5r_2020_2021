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

//float centerNodes[] = {x0,   y0,  x1,   y1,   x2,y2,   x3,   y3,   x4,   y4,  x5, y5,   x6,   y6,   x7,   y7 };
//float centerNodes[] = {-110, 580, 610, 330, 590, 105, 400, -630, 140, -550, -540, 510, -561, -161, -400, 230 };
//float centerNodes[] = {/*x0, x1, y2, y3, x4, x5, y6, y7*/};
float centerNodes[] = {-110, 610, 105, -630, 140, -540, -161, 300};
float nodeHeadings[] = {180, -135, -90, -45, 0, 45, 90, 135};


void navigateForever(){
  int count;
  if(OUR_COLOR){ //blue
    count = 2;
  } else {
    count = 6;
  }
  while(1){
    float currentX, currentY, currentHeading;
    static MAP_RECORD  local_map;
    jetson_comms.get_data( &local_map );
    currentHeading = local_map.pos.az*180/M_PI;
    currentX = local_map.pos.x;
    currentY = local_map.pos.y;
    count++;
    if(count == 8){
      count = 0;
    }
    //Brain.Screen.printAt(0,115, "currentHeading  %f", currentHeading);
    Brain.Screen.printAt(0,130, "1currentX  %f", currentX);
    Brain.Screen.printAt(0,145, "1currentY  %f", currentY);
    Brain.Screen.printAt(0,160, "Count %d", count);
    
    if(count % 2 == 0){ //even is facing side //odd facing corners
      setSpeed(10);
      snailTo(nodeHeadings[count]);
      setSpeed(30);
    }


    sideGoTo(centerNodes[count]);
    Brain.Screen.printAt(0,180, "here");
    Brain.Screen.printAt(0,200, "2currentY  %f", currentY);
    setSpeed(10);
    snailTo(nodeHeadings[count]);
    setSpeed(30);

    if(count == 0){
     this_thread::sleep_for(1000000);
    }
    
    pause();
    //descore(nodeHeadings[count]);
  }
}

