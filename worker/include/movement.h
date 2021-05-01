using namespace vex;

void driveAngle( int angleToDrive, int speed );
void driveAngleAbs( int angleToDrive, int speed );
void driveAngleFor( int dist, int angleToDrive, int speed );
void driveAngleForAbs( int dist, int angleToDrive, int speed );

extern void goTo( float dest_x, float dest_y, float dest_heading );
extern int turnTo( float dest_heading, int vel );

float toNormalAngle(float og_angle);
void snailTo(float dest_heading);
void sideGoTo(float finishCoordinate);


extern void poop( void );