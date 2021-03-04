// #include "vex.h"

// void centerBlock( void ) {
//   int count = 0;
//     float k;
//     double base;
//     int error;
//     double speedHDrive;
//     int ideal;
//     ideal=158;
//     int centerpoint;
//     centerpoint=Vision.largestObject.originX+Vision.largestObject.width/2;
//     int distanceFromBlock;
//     distanceFromBlock = abs(centerpoint-ideal);


//     while(distanceFromBlock > 20){ //can change ideal width
//       //Tell the vision sensor to capture a frame and look objects of the color stored in SIG_ORANGE.     
//       Vision.takeSnapshot(SIG_ORANGE);
//       //  Vision.takeSnapshot(SIG_PURPLE);
//       //  Vision.takeSnapshot(SIG_GREEN);
//       //If it detects at least one object with the color stored in SIG_ORANGE...
//       if(Vision.largestObject.exists){
//         Brain.Screen.clearScreen();
//         Brain.Screen.setOrigin(1,1);
//         Brain.Screen.drawRectangle(0,0,316,212);

//         Brain.Screen.print("distanceFromBlock: %d", distanceFromBlock);
//         Brain.Screen.newLine();
//         Brain.Screen.print("speed: %d", acos(-1));
//         Brain.Screen.newLine();
//         Brain.Screen.print("reps: %d", count);
//       //...draw a rectangle of equal size on the V5 Screen
//       Brain.Screen.drawRectangle(Vision.largestObject.originX,Vision.largestObject.originY, Vision.largestObject.width,Vision.largestObject.height,color::orange);

//       centerpoint=Vision.largestObject.originX+Vision.largestObject.width/2;

//       k = .2; //can change value of k
//       error = (centerpoint-ideal);
//       distanceFromBlock = abs(error);

//       if (error > 0){
//         base = 1;
//       } else {
//         base = -1;
//       }
//       if (distanceFromBlock < 20){
//         speedHDrive = error*k*.2;
//       } else {
//         speedHDrive = error*k*.6;
//       }
//       MiddleWheel.setVelocity(speedHDrive, percent);
//       MiddleWheel.spin(forward);
      
//       count += 1;
//     }
//     task::sleep(200);
//   } 
//     MiddleWheel.stop();
// }