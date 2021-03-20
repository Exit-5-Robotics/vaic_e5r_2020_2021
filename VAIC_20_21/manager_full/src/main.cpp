/*------------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                    */
/*    Description:  V5 project                                                  */
/*    https://kb.vex.com/hc/en-us/articles/360049619171-Coding-the-VEX-AI-Robot */
/*------------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// LinkA -           PORT11
// ballThree -       3WireC
// ballZero -        3WireE
// tilt -            PORT10
// goal -            3WireD
//
// leftIntake -      PORT1
// rightIntake -     PORT19
// botRoller -       PORT11
// topRoller -       PORT12
// Balls -           PORT10 (not in use)
//
// frontLeftWheel -  PORT2
// backLeftWheel -   PORT16
// backRightWheel -  PORT17
// frontRightWheel - PORT18
// leftDrive -       PORT16, PORT2
// rightDrive -      PORT17, PORT18
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// create instance of jetson class to receive location and other
// data from the Jetson nano
//
ai::jetson  jetson_comms;

#define EMPTY 0
#define BLUE 1
#define RED 2
#define OUR_COLOR RED

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT11 using the unique name robot_3063_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symmetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
#define  MANAGER_ROBOT    1

#if defined(MANAGER_ROBOT)
#pragma message("building for the manager")
ai::robot_link       link( PORT11, "robot_3063_1", linkType::manager );
#else
#pragma message("building for the worker")
ai::robot_link       link( PORT11, "robot_3063_1", linkType::worker );
#endif

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
  // goTo(0, 0, 0);
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

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // local storage for latest data from the Jetson Nano
    static MAP_RECORD       local_map;

    // RUn at about 15Hz
    int32_t loop_time = 66;

    // start the status update display
    thread t1(dashboardTask);
    // thread t2(testMovement);
    thread accel(values);
    // thread iso(redIsolation);

    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomousMain);

    // print through the controller to the terminal (vexos 1.0.12 is needed)
    // As USB is tied up with Jetson communications we cannot use
    // printf for debug.  If the controller is connected
    // then this can be used as a direct connection to USB on the controller
    // when using VEXcode.
    //
    //FILE *fp = fopen("/dev/serial2","wb");

    while(1) {
        // get last map data
        jetson_comms.get_data( &local_map );

        // set our location to be sent to partner robot
        link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

        //fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az  );

        // request new data    
        // NOTE: This request should only happen in a single task.    
        jetson_comms.request_map();

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
}