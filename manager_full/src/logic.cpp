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
std::map<int, int> goalAngle = {
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
mutex mu;

int inventory[3] = {EMPTY, EMPTY, EMPTY};

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

string positionToString( int x_pos, int y_pos ) { // converts integer positions to string
  x_pos = (x_pos >= 100) ? 72 : (x_pos <= -100) ? -72 : x_pos;
  y_pos = (y_pos >= 100) ? 72 : (y_pos <= -100) ? -72 : y_pos;
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

  // ballX = (int)(local_x + x_change); // REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP
  // ballY = (int)(local_y + y_change); // REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP REP

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
  while (true) {
    if (local_map.boxnum > 0) {
      for (int i=0; i<local_map.boxnum; i++) {
        if (local_map.boxobj[i].classID != 2 && abs(local_map.boxobj[i].x - 180) < 50) {
          ballOnField ball;
          ball.classID = local_map.boxobj[i].classID;
          ball.pos = getBallPosition(local_map.boxobj[i]);
          ball.age = 0;
          ballsOnField.push_back(ball);

          for (auto currentBall = ballsOnField.begin(); currentBall != ballsOnField.end(); /* NOTHING */)
          {
            if ((*currentBall).age > 5) {
              currentBall = ballsOnField.erase(currentBall);
            } else {
              (*currentBall).age++;
              ++currentBall;
            }
          }

          if (ballsOnField.size() > 50) { // clear if vector gets too big
            std::vector<ballOnField>().swap(ballsOnField);
          }

          if (local_map.boxobj[i].y < 115) // checks that it is SCORED
            // Brain.Screen.printAt(10, printPlace, "%d", local_map.boxobj[i].y);
            Brain.Screen.printAt(300, 20, getBallPosition(local_map.boxobj[i]).c_str());
            Brain.Screen.printAt(300, 80, "%d %d %d %d", local_map.boxobj[i].classID, local_map.boxobj[i].x, local_map.boxobj[i].y, local_map.boxobj[i].depth);
            mu.lock();
            mapScore[goalKeys[binBallPos(ball.pos)]] = local_map.boxobj[i].classID;
            mapAll[goalKeys[binBallPos(ball.pos)]][0] = local_map.boxobj[i].classID;
            mu.unlock();
          // printPlace += 20;
        }
      }
      stringSend = arrToString(mapScore);

      LinkA.send(stringSend.c_str());
    }
  }
}

int switchUp( void ) {
  int dump = 0;
  for (int i=0; i<local_map.boxnum; i++) {
    if (local_map.boxobj[i].classID != 2 && abs(local_map.boxobj[i].x - 180) < 20) {
      if (local_map.boxobj[i].y > 140 && local_map.boxobj[i].classID == OUR_COLOR) {// checks that BOTTOM IS OTHER COLOR
        return dump = 1; // move once
      } else if (local_map.boxobj[i].y < 140 && local_map.boxobj[i].y > 115 && local_map.boxobj[i].classID == OUR_COLOR)
        return dump = 2; // move twice
    }
  }
  return dump;
}

int assessGoal( void ) {
  Brain.Screen.printAt(10, 220, "Running Assess Goal");
  Brain.Screen.printAt(10, 200, "%d", local_map.boxnum);
  if (local_map.boxnum > 0) {
    for (int i=0; i<local_map.boxnum; i++) {
      if (local_map.boxobj[i].classID != 2 && abs(local_map.boxobj[i].x - 180) < 100) { // MAKES sure it's within center
        ballOnField ball;
        ball.classID = local_map.boxobj[i].classID;
        ball.pos = getBallPosition(local_map.boxobj[i]);
        ball.age = 0;

        if (local_map.boxobj[i].y < 115 && local_map.boxobj[i].classID == OTHER_COLOR) {// checks that it is SCORED
          Brain.Screen.printAt(50, 200, "other");
          while (local_map.boxobj[i].depth < 21) 
            robotDrive.drive(vex::reverse, 20, velocityUnits::pct);
          stopDriving();
          while (local_map.boxobj[i].x > 185 || local_map.boxobj[i].x < 175) {
            Brain.Screen.printAt(160, 20, "X value: %d", local_map.boxobj[i].x);
            driveAngle((local_map.boxobj[i].x-180)/abs(local_map.boxobj[i].x-180)*90, (int)(abs(local_map.boxobj[i].x - 180)/2));
          }
          stopDriving();
          int dump = switchUp();
          botRoller.spin(fwd, 50, vex::velocityUnits::pct);
          intake(20);
          stopDriving();

          if (dump == 0) {
            botRoller.spin(fwd, 100, vex::velocityUnits::pct);
            topRoller.spin(vex::reverse, 100, vex::velocityUnits::pct);
            task::sleep(1000);
            intake(10);
            task::sleep(1000);
            intake(10);
            task::sleep(1000);
          } else if (dump == 1) {
            adjustHold();
            score();
          } else if (dump == 2) {
            adjustHold();
            intake(10);
            score();
            adjustHold();
            score();
          }
          botRoller.stop();
          topRoller.stop();
          intakeWheels.stop();
          stopDriving();
          driveAngleFor(10, 180, 30);
          return 0;
        }
      }
    }
    // for (int i=0; i<local_map.boxnum; i++) {
    //   if (local_map.boxobj[i].classID != 2 && abs(local_map.boxobj[i].x - 180) < 100) { // MAKES sure it's within center
    //     ballOnField ball;
    //     ball.classID = local_map.boxobj[i].classID;
    //     ball.pos = getBallPosition(local_map.boxobj[i]);
    //     ball.age = 0;

    //     if (local_map.boxobj[i].y < 150 && local_map.boxobj[i].classID == OTHER_COLOR) {// checks that it is SCORED
    //       Brain.Screen.printAt(50, 200, "other");
    //       while (local_map.boxobj[i].depth < 21) 
    //         robotDrive.drive(vex::reverse, 20, velocityUnits::pct);
    //       stopDriving();
    //       while (local_map.boxobj[i].x > 185 || local_map.boxobj[i].x < 175) {
    //         Brain.Screen.printAt(160, 20, "X value: %d", local_map.boxobj[i].x);
    //         driveAngle((local_map.boxobj[i].x-180)/abs(local_map.boxobj[i].x-180)*90, (int)(abs(local_map.boxobj[i].x - 180)/2));
    //       }
    //       stopDriving();
    //       int dump = switchUp();
    //       botRoller.spin(fwd, 50, vex::velocityUnits::pct);
    //       intake(20);
    //       stopDriving();

    //       if (dump == 0) {
    //         botRoller.spin(fwd, 100, vex::velocityUnits::pct);
    //         topRoller.spin(vex::reverse, 100, vex::velocityUnits::pct);
    //         task::sleep(1000);
    //         intake(10);
    //         task::sleep(1000);
    //         intake(10);
    //         task::sleep(1000);
    //       } else if (dump == 1) {
    //         adjustHold();
    //         score();
    //       } else if (dump == 2) {
    //         adjustHold();
    //         intake(10);
    //         score();
    //         adjustHold();
    //         score();
    //       }
    //       botRoller.stop();
    //       topRoller.stop();
    //       intakeWheels.stop();
    //       stopDriving();
    //       driveAngleFor(10, 180, 30);
    //       return 0;
    //     }
    //   }
    // }
  }
  return 0;
  // robotDrive.driveFor(vex::reverse, 10, inches, 30, velocityUnits::pct);
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
  int minDist = 500;
  int getGoal = 0;
  float localX, localY, localH;
  link.get_local_location(localX, localY, localH);
  for (int i=0; i<8; i++) {
    int goalX = stringToX(goalLocation[i]);
    int goalY = stringToY(goalLocation[i]);
    if (sqrt(pow((goalX - localX),2) + pow((goalY - local_y),2)) < minDist) {
      getGoal = i;
      minDist = (int)sqrt(pow((goalX - localX),2) + pow((goalY - local_y),2));
    }
  }
  return getGoal;
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
