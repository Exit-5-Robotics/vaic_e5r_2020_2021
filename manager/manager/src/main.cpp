/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       E5R                                                       */
/*    Created:      Mon Aug 31 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// LinkA - PORT11
// botRoller - PORT
// topRoller - PORT
// Balls - PORT10
// 
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// create instance of jetson class to receive location and other
// data from the Jetson nano
//
ai::jetson  jetson_comms;

#define EMPTY 0
#define BLUE 1
#define RED 2
#define OUR_COLOR RED

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT1 using the unique name robot_32456_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
#define  MANAGER_ROBOT    1

#if defined(MANAGER_ROBOT)
#pragma message("building for the manager")
ai::robot_link link( PORT11, "robot_3063_1", linkType::manager );
#else
#pragma message("building for the worker")
ai::robot_link link( PORT11, "robot_3063_1", linkType::worker );
#endif

/*----------------------------------------------------------------------------*/

void decide_action( std::deque<int> &bot ) {
  // std::queue<int> bot; We would already have the balls in the bot
  std::deque<int> col;

  col.push_back(RED);
  col.push_back(BLUE);
  col.push_back(RED);

  switch(col.size()) {
    case 3:
      if (col[2] == OUR_COLOR) {
        // LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE
      } else {
        if (col[0] == OUR_COLOR) {
          // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
          // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
        } else {
          // INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE
          if (bot.empty()) {
            if (col[1] == OUR_COLOR) {
            // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
            // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
            // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
            } else {
              //IDK MAN IDK MAN IDK MAN IDK MAN IDK MAN
              //THROW IT ALL OUT
            }
          } else {
            // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
            // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
            // DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE
          }
        }
      }
      break;
    case 2:
      if (!bot.empty()) {

      } else {
        // PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP 
        // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
      }
      break;
    case 1:
      // WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH
      break;
    default:
      break;
  }
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

        // fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az  );

        // request new data        
        jetson_comms.request_map();

        ball_detect_stop_bot(4.5);

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
}
