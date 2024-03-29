void bumpedIntoSomething( void );

void driveAngle( int angleToDrive, int speed );
void driveAngleAbs( int angleToDrive, int speed );
void driveAngleFor( int dist, int angleToDrive, int speed );
void driveAngleForAbs( int dist, int angleToDrive, int speed );

extern void goToX( float dest_x, float dest_y, float dest_heading );
extern void goToY( float dest_x, float dest_y, float dest_heading );
extern int turnTo( float dest_heading, int vel );