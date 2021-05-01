#include "ai_jetson.h"

extern bool testChange( void );
extern float round( float var );
extern std::string arrToString( int (&arr)[9] );
extern int intLen( int n );

extern int stringToX( std::string pos );
extern int stringToY( std::string pos );

extern std::string positionToString( int x_pos, int y_pos );
extern std::string getBallPosition( fifo_object_box boxObj );

extern void cacheGoals( void );
extern void loadGoalsInfo(const char *message, const char *linkname, int32_t index, double value);
extern int getGoal( int x_pos, int y_pos );
extern int assessGoal( void );

extern std::string getClosest( void );
extern std::string getClosestOurColor( void );
extern int getClosestGoal( void );
extern void receiveMessages( void );