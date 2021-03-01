
#include "vex.h"
#include "ai_robot_link.h"

using namespace vex;

competition Competition;

// instance of jetson class to receive location and other data from the Jetson nano
ai::jetson  jetson_comms;


// Comment out the following definition to build for the worker robot
#define  MANAGER_ROBOT    1
#define OUR_COLOR    1; //red is 0, blue is 1

#if defined(MANAGER_ROBOT)
#pragma message("building for the manager")
ai::robot_link       link( PORT11, "robot_32456_1", linkType::manager );
#else
#pragma message("building for the worker")
ai::robot_link       link( PORT11, "robot_32456_1", linkType::worker );
#endif


void auto_Isolation(void) {
  
}


void auto_Interaction(void) {

}


/*----------------------------------------------------------------------------*/

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // local storage for latest data from the Jetson Nano
    static MAP_RECORD       local_map;

    // Run at about 15Hz
    int32_t loop_time = 66;

    // start the status update display
    thread t1(dashboardTask);

    int fieldMatrix[9][4] = {
    {0, 1, 0, 3},
    {1, 0, 2, 2},
    {1, 0, 1, 3},
    {0, 1, 2, 2},
    {0, 1, 2, 2},
    {0, 1, 2, 2},
    {1, 0, 2, 2},
    {1, 0, 2, 2},
    {2, 2, 2, 0}
    };

    


    while(1) {
        // get last map data
        jetson_comms.get_data( &local_map );

        // set our location to be sent to partner robot
        link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

        // request new data    
        // NOTE: This request should only happen in a single task.    
        jetson_comms.request_map();

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
}