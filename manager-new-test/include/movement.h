using namespace vex;
#include "ai_jetson.h"

void lookAround( void );
void stopDriving( void );

extern void intake( void );
extern void outtake( void );
extern int score( void );
extern void poop( void );

extern void intakeNoDrive( void );

extern void descore( void );
extern int adjustHold( void );

//

void reset(void);
double getHeading(void);

void toStartingPoint(int from, int endDir);
void toBestY(void);
void toFlipLine(void);

void turnTo(int targetAngle);

void alignTower0(void);
