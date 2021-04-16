extern bool testChange( void );
extern float round( float var );
extern std::string arrToString( int (&arr)[9] );
extern int intLen( int n );

extern int stringToX( std::string pos );
extern int stringToY( std::string pos );

extern std::string positionToString( int x_pos, int y_pos );
extern std::string getBallPosition( int ballDistance );

extern void cacheGoals( void );
extern void loadGoalsInfo(const char *message, const char *linkname, int32_t index, double value);
extern void receiveMessages( void );
extern int getGoal( int x_pos, int y_pos );