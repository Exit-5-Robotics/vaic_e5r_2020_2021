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
#include <deque>
#include <iostream>

#include "v5.h"
#include "v5_vcs.h"

#include "ai_jetson.h"
#include "ai_robot_link.h"

#include "robot-config.h"
#include "movement.h"
#include "logic.h"

#define EMPTY 0
#define BLUE 1
#define RED 2
#define OUR_COLOR RED

#define UP 1
#define DOWN -1

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

extern ai::jetson      jetson_comms;
extern ai::robot_link  link;

extern int dashboardTask( void );
extern int testMovement( void );
extern float round(float var);

extern void redIsolation( void );
extern void blueIsolation( void );