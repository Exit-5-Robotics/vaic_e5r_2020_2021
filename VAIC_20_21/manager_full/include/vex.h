/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// half of field width/height is 1829 mm or 72 in
// TODO: robotInFront in logic.cpp

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

#include "v5.h"
#include "v5_vcs.h"

#include "ai_jetson.h"
#include "ai_robot_link.h"

#include "robot-config.h"
#include "navigation.h"
#include "movement.h"
#include "logic.h"

#define EMPTY 3
#define BLUE 1
#define RED 0
#define OUR_COLOR RED
#define OTHER_COLOR BLUE

#define UP 1
#define DOWN -1

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
extern int inventory[3];

struct ballOnField {
  int classID;
  std::string pos;
};
extern std::vector<ballOnField> ballsOnField;

extern int dashboardTask( void );
extern int testMovement( void );
extern float round(float var);

extern void redIsolation( void );
extern void blueIsolation( void );