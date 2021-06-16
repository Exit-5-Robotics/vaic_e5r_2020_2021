using namespace vex;
#include "ai_jetson.h"

int getIntakeSpeed(void);

void lookAround( void );
void stopDriving( void );
double getLineColor(char which);
void driveToLine(int dir,int speed, int reverseTime, char whichSensor);

extern void intake( bool useBot );
extern void outtake( void );
extern int score( void );
extern void poop( void );

extern void intakeNoDrive( void );

extern void descore( void );
extern int adjustHold( void );
extern int adjustWIntake( void );

//

void reset(void);
double getHeading(void);

void toStartingPoint(int from, int endDir);
void toBestY(void);
void toFlipLine(void);

void turnTo(int targetAngle);

void alignTower0(void);
int getRed(void);