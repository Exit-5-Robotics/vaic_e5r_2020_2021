/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\wazsu                                            */
/*    Created:      Fri Feb 19 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// dumpPoint --> pathPoint --> (possibly) pathPoint --> dumpPoint
float dumpPoint[] = {/*x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10, x11, y11, x12, y12*/};
float pathPoint[] = {/*x1, y1, x2, y2, x3, y3, x4, y4*/};
float minTowerDistance = 10; // distance between towers that are next to each other, plug this in later


float getDistance(float x1, float y1, float x2, float y2){
  return sqrt(pow(x2 - x1, 2) + pow(x2 - x1, 2));
}

int findNode(int startTower, int endTower, float startX, float startY, float endX, float endY){
  //0. situations with no node
  if (endTower == 8 || getDistance(startX, startY, endX, endY) <= minTowerDistance){ 
    // if towers are next to each other (distance between them is less than a specific value) or going to middle tower
    return -1;
  }

  //1. eliminate node directly in front if either tower is 0 , 1, 2, or 3
  bool isStartEliminated, isEndEliminated;
  if(startTower < 4){
    isStartEliminated = true;
  }
  if(endTower < 4){
    isEndEliminated = true;
  }

  //2. shortest distance
  float shortestDistance = 0;
  int chosenNode;
  for(int i = 0; i < 4; i ++){
    float tempDistance = getDistance(startX, startY, pathPoint[i*2], pathPoint[i*2 + 1]) + getDistance(endX, endY, pathPoint[i*2], pathPoint[i*2 + 1]);
    if( !(isStartEliminated && i == startTower) || !(isEndEliminated && i == endTower) ){ //not one of the eliminated nodes
      if( shortestDistance == 0 || tempDistance < shortestDistance ){ // no data or new best node
        chosenNode = i;
        shortestDistance = tempDistance;
      }  // else: skip, keep old node as best
    }
  }
  
  return chosenNode;
}

void moveToNextTower(float StartTowerX, float startTowerY, float endTowerX, float endTowerY, int node){
  // check if there is actually a node !(node == -1)
    //if yes: go to node
    //if no: skip
  //go to tower
}

void moveToTower(int startTower, int endTower, float startTowerX, float startTowerY){ //assign tower values 0-8
  float endTowerX, endTowerY;
  //check if tower 8 is used
  if(endTower == 9){
    if(startTower == 0 || startTower == 1 || startTower == 2){ //12
      endTowerX = dumpPoint[22];
      endTowerY = dumpPoint[23];
    } else if(startTower == 5 || startTower == 6 || startTower == 7){ //10
      endTowerX = dumpPoint[18];
      endTowerY = dumpPoint[19];
    }else if(startTower == 3){ //9
      endTowerX = dumpPoint[16];
      endTowerY = dumpPoint[17];
    } else{ //11
      endTowerX = dumpPoint[20];
      endTowerY = dumpPoint[21];
    }
  } else {
    endTowerX = dumpPoint[endTower*2];
    endTowerY = dumpPoint[endTower*2 + 1];
  }
  //go to the tower
  moveToNextTower(startTowerX, startTowerY, endTowerX, endTowerY, findNode(startTower, endTower, startTowerX, startTowerY, endTowerX, endTowerY));
  //square to tower
  //run tower program
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


}