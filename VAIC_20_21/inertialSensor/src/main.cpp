/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       bruh                                                     */
/*    Created:      Fri Nov 01 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

/*----------------------------------------------------------------------------*/
// This would need moving to robot-config.cpp if using graphical configuration
//
// A global instance of vex::brain used for printing to the V5 brain screen

// define your global instances of motors and other devices here
vex::inertial    Inertial( vex::PORT4 );

/*----------------------------------------------------------------------------*/

// int main() {
//   vexcodeInit();
// Inertial.calibrate();

// while (Inertial.isCalibrating()) {
//   wait(100, msec);
// }
// Brain.Screen.clearScreen();
// // LeftMotor.spin(forward);
// // RightMotor.spin(reverse);

//   int pos;
//   while (true) {
//     Brain.Screen.setCursor(3, 3);
//     pos = Inertial.rotation(degrees);
//     Brain.Screen.print("%d", pos);
//     if (Inertial.rotation(degrees) >= 200.0)
//     break;
//   }

// Brain.Screen.setCursor(3, 3);
// Brain.Screen.print("yeeyoink");
// wait(1, seconds);
// }


int main() {
    inertial::quaternion  Inertial_quaternion;

    Inertial.calibrate();

    while(1) {
        // get the quaternion data
        Inertial_quaternion = Inertial.orientation();

        Brain.Screen.clearScreen();        

        Brain.Screen.setFont( mono15 );
        Brain.Screen.setPenColor( white );
        Brain.Screen.setFillColor( black );
        
        Brain.Screen.printAt( 20,  30, "GX  %8.3f", Inertial.gyroRate( xaxis, dps ) );
        Brain.Screen.printAt( 20,  45, "GY  %8.3f", Inertial.gyroRate( yaxis, dps ) );
        Brain.Screen.printAt( 20,  60, "GZ  %8.3f", Inertial.gyroRate( zaxis, dps ) );

        Brain.Screen.printAt( 20,  90, "AX  %8.3f", Inertial.acceleration( xaxis ) );
        Brain.Screen.printAt( 20, 105, "AY  %8.3f", Inertial.acceleration( yaxis ) );
        Brain.Screen.printAt( 20, 120, "AZ  %8.3f", Inertial.acceleration( zaxis ) );

        Brain.Screen.printAt( 20, 150, "A   %8.3f", Inertial_quaternion.a );
        Brain.Screen.printAt( 20, 165, "B   %8.3f", Inertial_quaternion.b );
        Brain.Screen.printAt( 20, 180, "C   %8.3f", Inertial_quaternion.c );
        Brain.Screen.printAt( 20, 195, "D   %8.3f", Inertial_quaternion.d );

        Brain.Screen.printAt( 150, 30, "Roll     %7.2f", Inertial.roll() );
        Brain.Screen.printAt( 150, 45, "Pitch    %7.2f", Inertial.pitch() );
        Brain.Screen.printAt( 150, 60, "Yaw      %7.2f", Inertial.yaw() );

        Brain.Screen.printAt( 150, 90, "Heading  %7.2f", Inertial.heading() );
        Brain.Screen.printAt( 150,105, "Rotation %7.2f", Inertial.rotation() );

        if( Inertial.isCalibrating() )
          Brain.Screen.printAt( 20,225, "Calibration  In Progress" );
        else
          Brain.Screen.printAt( 20,225, "Calibration  Done" );

        Brain.Screen.render();

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}