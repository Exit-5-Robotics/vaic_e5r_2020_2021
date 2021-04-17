#include "vex.h"

using namespace vex;
using namespace std;
int mapScore[9] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
int mapAll[9][3] = {{EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY}};

std::map<std::string, int> goalKeys = { // converts goal position to the number of the goal
  {"+00+50", 0},
  {"+50+00", 1},
  {"+00-50", 2},
  {"-50+00", 3},
  {"-50+50", 4},
  {"-50-50", 5},
  {"+50+50", 6},
  {"+50-50", 7},
  {"+00+00", 8},
};
std::map<int, std::string> goalLocation = { // converts goal position to the number of the goal
  {0, "+00+50"},
  {1, "+50+00"},
  {2, "+00-50"},
  {3, "-50+00"},
  {4, "-50+50"},
  {5, "-50-50"},
  {6, "+50+50"},
  {7, "+50-50"},
  {8, "+00+00"},
};

// goal height is about 12, 19, 26
// so thresholds are 16, 22

bool testChange() {
  bool isDiff = false;

  float first_x, first_y, first_heading, next_heading;
  link.get_local_location(first_x, first_y, first_heading);
  task::sleep(100);
  link.get_local_location(first_x, first_y, next_heading);

  if (first_heading != next_heading) isDiff = true;

  return isDiff;
}

// bool robotInFront( int distPos, ) {
  // if objdist + current x or y depending on direction == 72 in then it's probably a wall
//   if (distPos==1 && (dist.objectDistance(distanceUnits::in) + ))
// }

float round(float var) {
    float value = (int)(var * 100 + .5); 
    return (float)value / 100;
}

string arrToString( int (&arr)[9] ) {
  
    ostringstream os;
    for (int i: arr) {
        os << i;
    }
 
    string str(os.str());

    return str;
}

int intLen( int n ) {
  unsigned int number_of_digits = 0;

  do {
      ++number_of_digits; 
      n /= 10;
  } while (n);
  return number_of_digits;
}

string positionToString( int x_pos, int y_pos ) {
  int x_diff = (abs(x_pos/10) > 0) ? 0 : 1;
  int y_diff = (abs(y_pos/10) > 0) ? 0 : 1;
  char x_sign = (x_pos >= 0) ? '+' : '-';
  char y_sign = (y_pos >= 0) ? '+' : '-';

  string xStrDiff(x_diff, '0');
  string yStrDiff(y_diff, '0');

  string s = SSTR(x_sign << xStrDiff << x_pos << y_sign << yStrDiff << y_pos);
  
  return s;
}

int stringToX( string pos ) {
  int xStr = atoi(pos.substr(1, 2).c_str());
  if (pos[0] == '-') xStr *= -1;
  return xStr;
}

int stringToY( string pos ) {
  int yStr = atoi(pos.substr(4, 2).c_str());
  if (pos[3] == '-') yStr *= -1;
  return yStr;
}

string getBallPosition( MAP_OBJECTS mapObj ) {
  int ballX = mapObj.positionX, ballY = mapObj.positionY;

  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);
  current_x /= 25.4, current_y /= 25.4;

  ballX = current_x - ballX;
  ballY = current_y - ballY;

  return positionToString(ballX, ballY);
}

void cacheGoals( void ) { // should also be a long-running thread should also be a long-running thread should also be a long-running thread should also be a long-running thread
  // move out
  static MAP_RECORD  local_map;
  float current_x, current_y, current_heading;
  int mapnum;
  
  string stringSend;
  
  while (true) {
    link.get_local_location(current_x, current_y, current_heading);
    jetson_comms.get_data( &local_map );
    mapnum = local_map.mapnum;
    
    if (mapnum > 0) {
      for (int i=0; i<mapnum; i++) {
        if ((local_map.mapobj[i].age < 100) && (local_map.mapobj[i].positionZ/25.4 > 22)) {

          // get_id
          mapScore[i] = local_map.mapobj[i].classID; // MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE
          mapAll[i][0] = local_map.mapobj[i].classID;
          // Brain.Screen.printAt(10, 20, getBallPosition(local_map.boxobj[i].depth).c_str()); // broken line
        }
      }
      stringSend = arrToString(mapScore);

      LinkA.send(stringSend.c_str());
    }
  }
}

int getGoal( int x_pos, int y_pos ) {
  string s = positionToString(x_pos, y_pos);
  int goalNum = goalKeys.at(s);
  
  Brain.Screen.printAt(10, 40, s.c_str());
  Brain.Screen.printAt(10, 60, "%d", goalNum);

  return goalNum;
}

void loadGoalsInfo(const char *message, const char *linkname, int32_t index, double value) {
    // convert received message to integer array
    // add the changed values to the mapAll
  ;
}

void receiveMessages( void ) {
  while (true) {
    LinkA.received(loadGoalsInfo);
  }
}





























bool checkDescore(){
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  int ballCount = 0;
  for(int i = 0; i < local_map.boxnum; i++){
    jetson_comms.get_data( &local_map );

    if(local_map.boxobj[i].classID != 2){
      ballCount++;
    }
  }

  if(ballCount >= 3){
    int smallestHeight[] = {local_map.boxobj[0].y, 0};
    for(int i = 1; i < local_map.boxnum; i++){
      jetson_comms.get_data( &local_map );

      if(local_map.boxobj[i].y < smallestHeight[0] && local_map.boxobj[i].classID != 2){
        smallestHeight[0] = local_map.boxobj[i].y;
        smallestHeight[1] = i;
      }
    }
    if(local_map.boxobj[smallestHeight[1]].classID != OUR_COLOR){
      return true;
    }
  }
  return false;
}
