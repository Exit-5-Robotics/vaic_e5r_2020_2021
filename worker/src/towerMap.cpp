#include "vex.h"

using namespace vex;
using namespace std;

int mapScore[9] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
int mapAll[9][3] = {{EMPTY, EMPTY, EMPTY}, // top, mid, bot
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
std::map<int, int> goalAngle = { //me just guessing,  but converts goal position to heading of goal?????? - annica  ps. im dumb
  {0, 0},
  {1, 90},
  {2, 180},
  {3, 270},
  {4, 315},
  {5, 225},
  {6, 45},
  {7, 135},
  {8, -1}
};

std::vector<ballOnField> ballsOnField;

//int inventory[3] = {EMPTY, EMPTY, EMPTY};

// goal height is about 12, 19, 26
// so thresholds are 16, 22

bool testChange() {
  bool isDiff = false;

  float first_heading, next_heading;
  first_heading = local_heading;
  task::sleep(100);
  next_heading = local_heading;

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

  string s = SSTR(x_sign << xStrDiff << abs(x_pos) << y_sign << yStrDiff << abs(y_pos));
  
  return s;
}

int stringToX( string pos ) {
  return (pos[0] == '-') ? atoi(pos.substr(1, 2).c_str())*-1 : atoi(pos.substr(1, 2).c_str());
}

int stringToY( string pos ) {
  return (pos[3] == '-') ? atoi(pos.substr(4, 2).c_str())*-1 : atoi(pos.substr(4, 2).c_str());
}

string getBallPosition( fifo_object_box boxObj ) {
  // does not return height
  int ballX = boxObj.x;
  int ballY = boxObj.y;
  int ballDist = (int)(boxObj.depth/25.4);

  float theta_x = atan2((float)(ballX - 180), (float)312); // left-right angle of ball
  float theta_y = atan2((float)(ballY - 126), (float)190); // up-down angle of ball

  float x = sin(theta_x) * cos(theta_y);
  // float y = sin(theta_y);
  float z = cos(theta_x) * cos(theta_y);

  float forward = z*ballDist;
  float sideways = x*ballDist;

  float x_change = forward*sin(local_heading*M_PI/180) + sideways*sin(local_heading*M_PI/180);
  float y_change = forward*cos(local_heading*M_PI/180) + sideways*cos(local_heading*M_PI/180);

  ballX = (int)(local_x + x_change);
  ballY = (int)(local_y + y_change);

  return positionToString(ballX, ballY);
}

string binBallPos( string pos ) {
  int ballX = stringToX(pos), ballY = stringToY(pos);
  if (ballX > 36) {
    ballX = 50;
  } else if (ballX > -36) {
    ballX = 0;
  } else {
    ballX = -50;
  }
  if (ballY > 36) {
    ballY = 50;
  } else if (ballY > -36) {
    ballY = 0;
  } else {
    ballY = -50;
  }

  return positionToString(ballX, ballY);
}

void cacheGoals( void ) { // should also be a long-running thread should also be a long-running thread should also be a long-running thread
  string stringSend;
  Brain.Screen.printAt(10, 100, "Starting cache goals");
  if (local_map.boxnum > 0) {

    for (int i=0; i<local_map.boxnum; i++) {
      if (local_map.boxobj[i].classID != 2) {
        ballOnField ball;
        ball.classID = local_map.boxobj[i].classID;
        ball.pos = getBallPosition(local_map.boxobj[i]);
        ball.age = 0;
        ballsOnField.push_back(ball);

        for (auto currentBall = ballsOnField.begin(); currentBall != ballsOnField.end(); /* NOTHING */)
        {
          if ((*currentBall).age > 50) {
            currentBall = ballsOnField.erase(currentBall);
          } else {
            (*currentBall).age++;
            ++currentBall;
          }
        }  

        if (local_map.boxobj[i].y < 115) // checks that it is SCORED
          // Brain.Screen.printAt(10, printPlace, "%d", local_map.boxobj[i].y);
          // Brain.Screen.printAt(300, printPlace, getBallPosition(local_map.boxobj[i]).c_str());
          mapScore[goalKeys[ball.pos]] = local_map.boxobj[i].classID;
          mapAll[goalKeys[ball.pos]][0] = local_map.mapobj[i].classID;
        // printPlace += 20;
      }
    }
    stringSend = arrToString(mapScore);

    LinkA.send(stringSend.c_str());
  }
}

void loadGoalsInfo(const char *message, const char *linkname, int32_t index, double value) {
    // convert received message to integer array
    // add the changed values to the mapAll
  ;
}

string getClosest( void ) {
  int dist = 200; // distance to closest ball
  string ballPos;
  for (unsigned i=0; i<ballsOnField.size(); i++) {
    if ((int)sqrt(pow(stringToX(ballsOnField.at(i).pos), 2) + pow(stringToY(ballsOnField.at(i).pos), 2)) < dist) {
      ballPos = ballsOnField.at(i).pos;
    }
  }
  return ballPos;
}

string getClosestOurColor( void ) {
  int dist = 200; // distance to closest ball
  string ballPos;
  for (unsigned i=0; i<ballsOnField.size(); i++) {
    if ((int)sqrt(pow(stringToX(ballsOnField.at(i).pos), 2) + pow(stringToY(ballsOnField.at(i).pos), 2)) < dist && ballsOnField.at(i).classID == OUR_COLOR) {
      ballPos = ballsOnField.at(i).pos;
    }
  }
  return ballPos;
}

int getClosestGoal( void ) {
  int minDist = 100;
  int getGoal = 0;
  for (int i=0; i<8; i++) {
    int goalX = stringToX(goalLocation[i]);
    int goalY = stringToY(goalLocation[i]);
    if (sqrt(pow((goalX - local_x),2) + pow((goalY - local_y),2)) < minDist) {
      getGoal = i;
      minDist = (int)sqrt(pow((goalX - local_x),2) + pow((goalY - local_y),2));
    }
  }
  return getGoal;
}

void receiveMessages( void ) {
  while (true) {
    LinkA.received(loadGoalsInfo);
  }
}
