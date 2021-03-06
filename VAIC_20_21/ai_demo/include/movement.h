using namespace vex;

extern void goTo( float dest_x, float dest_y, float dest_heading );
extern void turnTo( float dest_heading, int vel );

extern void intake( int speed );
extern void outtake( void );
extern void score( void );
extern void poop( void );

extern void descore( void );
extern int adjustHold( void );