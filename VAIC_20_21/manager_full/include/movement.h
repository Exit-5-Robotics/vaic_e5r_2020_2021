using namespace vex;

void driveAngle( int angleToDrive, int speed );
void driveAngleAbs( int angleToDrive, int speed );
void driveAngleFor( int dist, int angleToDrive, int speed );
void driveAngleForAbs( int dist, int angleToDrive, int speed );

extern void goTo( float dest_x, float dest_y, float dest_heading );
extern int turnTo( float dest_heading, int vel );

extern void intake( int speed );
extern void outtake( void );
extern void score( void );
extern void poop( void );

extern void intakeNoDrive( void );

extern void descore( void );
extern int adjustHold( void );