#include "vex.h"
using namespace vex;

/*
To do:
- collect centerNodes[] positions
- collect nodeHeadings[] positions
- test turnTO() with nodeHeadings[] info
- test goTo() with centerNodes[] info
- see if stuff works out
- see if current descore() works
- change descore() so it starts at a centerNode and returns to the same CenterNode
- copy the manager communication stuff over
- update the manager at designated spot in descore()
*/

int order[] = {3, 4, 0, 6, 1, 7, 2, 5}; //automatically red

float centerNodes[] = {/*x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8*/};
float nodeHeadings[] = {/*heading 0, heading 1, heading 2, heading 3, heading 4, heading 5, heading 6, heading 7, heading 8*/};

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

void navigateForever(){
  int count = 0;
  while(1){
    if(count == 9){
      count = 0;
    }

    descore();

    goTo(centerNodes[order[count*2]], centerNodes[order[count*2 + 1]], nodeHeadings[count]/*turns 45 degrees*/);
    count++;
  }
}

