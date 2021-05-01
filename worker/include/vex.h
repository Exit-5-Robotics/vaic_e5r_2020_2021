/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

#include "v5.h"
#include "v5_vcs.h"

#include "ai_jetson.h"
#include "ai_robot_link.h"
#include "descore.h"
#include "drive.h"
#include "movement.h"
#include "navigation.h"
#include "towerMap.h"

#include "robot-config.h"

#define RED    0
#define BLUE   1
#define OUR_COLOR    BLUE
#define EMPTY 3
#define OTHER_COLOR BLUE

extern float local_x;
extern float local_y;
extern float local_heading;

extern int distPosition;

extern std::map<std::string, int> goalKeys;
extern std::map<int, std::string> goalLocation;

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

extern ai::jetson      jetson_comms;
extern ai::robot_link  link;
extern MAP_RECORD       local_map;
extern bool driving;

extern int mapScore[9];
extern int mapAll[9][3];

extern int dashboardTask( void );

extern void (redIsolation());
extern void (blueIsolation());

struct ballOnField {
  int classID;
  std::string pos;
  int age;
};
extern std::vector<ballOnField> ballsOnField;

