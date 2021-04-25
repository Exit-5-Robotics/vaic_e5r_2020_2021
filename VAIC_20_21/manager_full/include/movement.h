using namespace vex;
#include "ai_jetson.h"

void lookAround( void );
void stopDriving( void );

extern void intake( int speed );
extern void outtake( void );
extern void score( void );
extern void poop( void );

extern void intakeNoDrive( void );

extern void descore( void );
extern int adjustHold( void );
extern void moveBackFromBall( fifo_object_box boxObj );
extern void centerBall( fifo_object_box boxObj );

extern int moveDistSensor( int direc ); // returns an int: 1 means it is in the UP position, -1 means it is in the DOWN position
extern void distSensorControl( void );