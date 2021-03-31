/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       E5R                                                       */
/*    Created:      Mon Aug 31 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// LinkA - PORT 11
// RF    - PORT 12
// RB    - PORT 14
// LF    - PORT 18
// LB    - PORT 13
// Intake - PORT 9
// Roller - PORT 8
// 
// 
// direction settings FOR NAVIGATION: idk if this helps but here
  //0 = cw rotation
  //1 = ccw rotation
  //2 = forward
  //3 = backward
  //4 = left back
  //5 = right forward
  //6 = left forward
  //7 = right back
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;  

// create instance of jetson class to receive location and other
// data from the Jetson nano
//
ai::jetson  jetson_comms;

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT1 using the unique name robot_32456_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
// #define  MANAGER_ROBOT    1


#if defined(MANAGER_ROBOT)
#pragma message("building for the manager")
ai::robot_link link( PORT11, "robot_3063_1", linkType::manager );
#else
#pragma message("building for the worker")
ai::robot_link link( PORT11, "robot_3063_1", linkType::worker );
#endif

static MAP_RECORD       local_map;

/*----------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          Auto_Isolation Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous isolation  */
/*  phase of a VEX AI Competition.                                           */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void auto_Isolation(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  if (OUR_COLOR == RED) {
    // red-side isolation code
    // cannot go to negative x values
  } else if (OUR_COLOR == BLUE) {
    // blue-side isolation code
    // cannot go to positive x values
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        Auto_Interaction Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous interaction*/
/*  phase of a VEX AI Competition.                                           */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void auto_Interaction(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  Brain.Screen.printAt( 10, 90, "auto_Interaction" );

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          AutonomousMain Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/

bool firstAutoFlag = true;

void autonomousMain(void) {
  Brain.Screen.printAt( 10, 10, "autonomousMain" );
  // ..........................................................................
  // The first time we enter this function we will launch our Isolation routine
  // When the field goes disabled after the isolation period this task will die
  // When the field goes enabled for the second time this task will start again
  // and we will enter the interaction period. 
  // ..........................................................................

  if(firstAutoFlag)
    auto_Isolation();
  else 
    auto_Interaction();

  firstAutoFlag = false;
}

/*----------------------------------------------------------------------------*/

void 
get_obj(const char *message, const char *linkname, double i) {
  printf("%f", i);
  Brain.Screen.clearScreen();
}

void workerDuties(){
  this_thread::sleep_for(10);
  setSpeed(40);
  //descore();
  robotDrive.turnFor(left, 360, vex::rotationUnits::deg, 5, vex::velocityUnits::pct, false);
  //turnTo(180, 50);
  Brain.Screen.printAt(5, 155, "seven");

}



int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // local storage for latest data from the Jetson Nano
    static MAP_RECORD       local_map;

    // RUn at about 15Hz
    int32_t loop_time = 66;

    // start the status update display
    thread t1(dashboardTask);

    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomousMain);


    // print through the controller to the terminal (vexos 1.0.12 is needed)
    // As USB is tied up with Jetson communications we cannot use
    // printf for debug.  If the controller is connected
    // then this can be used as a direct connection to USB on the controller
    // when using VEXcode.
    //
    //FILE *fp = fopen("/dev/serial2","wb");

    LinkA.received("object", get_obj);

    thread t2(workerDuties);

    while(1) {
        // get last map data
        jetson_comms.get_data( &local_map );

        // set our location to be sent to partner robot
        link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

        // fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az  );

        // request new data        
        jetson_comms.request_map();

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
}