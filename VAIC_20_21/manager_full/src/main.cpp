/*------------------------------------------------------------------------------*/
/*    Module:       main.cpp                                                    */
/*    Description:  V5 project                                                  */
/*    https://kb.vex.com/hc/en-us/articles/360049619171-Coding-the-VEX-AI-Robot */
/*------------------------------------------------------------------------------*/

// SOMETHING TO TRY BELOW

// ---- START VEXCODE CONFIGURED DEVICES ----
// LinkA -           PORT11
// ballThree -       3WireC
// ballZero -        3WireE
// tilt -            PORT10
// goal -            3WireD
// dist -            PORT5
//
// leftIntake -      PORT1
// rightIntake -     PORT19
// botRoller -       PORT11
// topRoller -       PORT12
// distMotor -       PORT8 (300 degrees turning)
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
float local_x, local_y, local_heading;
MAP_RECORD       local_map;
bool driving = false;

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

// TRY SOMETHING ALONG THESE LINES TO GO TO WORKER ROBOT TRY SOMETHING ALONG THESE LINES TO GO TO WORKER ROBOT TRY SOMETHING ALONG THESE LINES TO GO TO WORKER ROBOT
// void goToContinuous( ) {
//   while (true) {
//     thread go(goTo);
//     task::sleep(100);
//     go.join();
//   }
// }
mutex mutoo;

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
    redIsolation();
  } else if (OUR_COLOR == BLUE) {
    blueIsolation();
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
  // Brain.Screen.printAt(10, 80, "Starting auto int");
  float localX, localY, localH;
  while (true) {
    link.get_local_location(localX, localY, localH);
    Brain.Screen.printAt(10, 40, "%.2f %.2f %.2f", local_x, local_y, local_heading);
    if (localX != 0) {
      task::sleep(15000);
      Brain.Screen.printAt(10, 40, "%.2f %.2f %.2f", local_x, local_y, local_heading);
      // int closestGoal = getClosestGoal();
      int closestGoal = OUR_COLOR==BLUE ? 5 : 6;
      int closestGoalX, closestGoalY;

      Brain.Screen.printAt(10, 20, "%d", closestGoal);
      
      while(true) { // actual while loop
        link.get_local_location(localX, localY, localH);
        closestGoalX = stringToX(goalLocation[closestGoal]);
        closestGoalY = stringToY(goalLocation[closestGoal]);
        if (closestGoalX == 0 && closestGoalY != 0) {
          int ySign = closestGoalY > 0 ? 1 : -1;
          closestGoalY = (abs(closestGoalY) - 5)*ySign;
          closestGoalX -= 10*ySign;
          Brain.Screen.printAt(300, 160, "%d %d", closestGoalX, closestGoalY);
          goToX(closestGoalX, closestGoalY, goalAngle[closestGoal]);
          stopDriving();
          task::sleep(250);
          driveAngleFor(10, 90, 30);
          task::sleep(250);
          driveAngleFor(10, 180, 30);
          task::sleep(500);
        } else if (closestGoalY == 0 && closestGoalX != 0) {
          int xSign = closestGoalX > 0 ? 1 : -1;
          closestGoalX = (abs(closestGoalX) - 5)*xSign;
          closestGoalY += 10*xSign;
          Brain.Screen.printAt(300, 160, "%d %d", closestGoalX, closestGoalY);
          goToY(closestGoalX, closestGoalY, goalAngle[closestGoal]);
          stopDriving();
          task::sleep(250);
          driveAngleFor(10, 90, 30);
          task::sleep(250);
          driveAngleFor(10, 180, 30);
          task::sleep(500);
        } else if ((closestGoalX > 0 && closestGoalY > 0) || (closestGoalX < 0 && closestGoalY < 0)) {
          // +50+50 --> +30+40, +50-50 --> +50-40, -50-50 --> -30-40, -50+50 --> -50+40
          int xSign = closestGoalX > 0 ? 1 : -1;
          closestGoalX = (abs(closestGoalX) - 20)*xSign;
          closestGoalY = (abs(closestGoalY) - 10)*xSign;
          goToX(closestGoalX, closestGoalY, goalAngle[closestGoal]);
          goToY(closestGoalX, closestGoalY, goalAngle[closestGoal]);
          stopDriving();
          task::sleep(250);
          driveAngleFor(10, 90, 30);
          task::sleep(500);
        } else {
          int ySign = closestGoalY > 0 ? 1 : -1;
          closestGoalY = (abs(closestGoalY) - 20)*ySign;
          closestGoalX = (abs(closestGoalX) - 20)*ySign*-1;
          goToX(closestGoalX, closestGoalY, goalAngle[closestGoal]);
          goToY(closestGoalX, closestGoalY, goalAngle[closestGoal]);
          stopDriving();
          task::sleep(250);
          driveAngleFor(10, 90, 30);
          task::sleep(500);

        }
        robotDrive.stop();
        assessGoal();
        Brain.Screen.clearScreen();
        driveAngleFor(10, 90, 30);
        switch (closestGoal) {
          case 0:
            closestGoal = 6;
            break;
          case 6:
            closestGoal = 1;
            break;
          case 1:
            closestGoal = 7;
            break;
          case 7:
            closestGoal = 2;
            break;
          case 2:
            closestGoal = 5;
            break;
          case 5:
            closestGoal = 3;
            break;
          case 3:
            closestGoal = 4;
            break;
          default:
            closestGoal = 0;
            break;
        }
      }
    }
  }
  // while (inventory[0] == EMPTY) {
    
  // }
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
    // static MAP_RECORD       local_map;

    // Run at about 15Hz
    int32_t loop_time = 66;

    // thread t1(dashboardTask);
    
    // thread distanceSensor(distSensorControl); // assumes dist sensor starts UP
    thread prac(auto_Interaction);
    prac.setPriority(100);

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
        
        local_x = local_map.pos.x/25.4;
        local_y = local_map.pos.y/25.4;
        local_heading = local_map.pos.az*180/M_PI;

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