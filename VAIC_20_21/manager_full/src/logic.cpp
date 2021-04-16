#include "vex.h"

using namespace vex;
using namespace std;

int mapScore[3][3] = {{0, 0, 0},  // 00, 01, 02
                      {0, 0, 0},  // 10, 11, 12
                      {0, 0, 0}}; // 20, 21, 22

// hashmap??

deque<int> goalsVisiting;

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

// goal height is about 12, 19, 26
// so thresholds are 16, 22

float round(float var) {
    float value = (int)(var * 100 + .5); 
    return (float)value / 100;
}

std::string arrToString( int (&arr)[9] ) {
  
    std::ostringstream os;
    for (int i: arr) {
        os << i;
    }
 
    std::string str(os.str());

    return str;
}

void cacheGoals( void ) { // should also be a long-running thread
  // move out
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  float current_x, current_y, current_heading;
  link.get_local_location(current_x, current_y, current_heading);

  int opponentScored[9] = {2};
  std::string stringSend;
  // int heading_direction = current_heading/; 
  // assume robot is facing goal
  
  int mapnum = local_map.mapnum;
  if (mapnum > 0) {
    for (int i=0; i<mapnum; i++) {
      if (local_map.mapobj[i].age == 100 && local_map.mapobj[i].positionZ/25.4 > 22 && local_map.mapobj[i].classID == OTHER_COLOR) {
        // get_id
        opponentScored[i] = OTHER_COLOR; // MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE MUST CHANGE

  //       // const int prevToFind = 10;
  //       // auto findResult = std::find_if(std::begin(table), std::end(table), [&](const std::pair<int, struct_t*> &pair)
  //       // {
  //       //     return pair.second->prev == prevToFind;
  //       // });

  //       // int foundKey = 0; // You might want to initialise this to a value you know is invalid in your map
  //       // struct_t *foundValue = nullptr
  //       // if (findResult != std::end(table))
  //       // {
  //       //     foundKey = findResult->first;
  //       //     foundValue = findResult->second;

  //       //     // Now do something with the key or value!
  //       // }
      }
    }
    stringSend = arrToString(opponentScored);
    Brain.Screen.printAt(10, 20, stringSend.c_str());

    LinkA.send(stringSend.c_str());
  }
}

void loadInfo(const char *message, const char *linkname, double value) {
  ;
}

void receiveMessages( void ) {
  while (true) {
    LinkA.received("lalala", loadInfo); // FIX
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

void decide_action( deque<int> &bot ) {
  // std::queue<int> bot; We would already have the balls in the bot
  deque<int> col;

  col.push_back(RED);
  col.push_back(BLUE);
  col.push_back(RED);

  switch(col.size()) {
    case 3:
      if (col[2] == OUR_COLOR) {
        // LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE LEAVE
      } else {
        if (col[0] == OUR_COLOR) {
          // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
          // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
        } else {
          // INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE INTAKE
          if (bot.empty()) {
            if (col[1] == OUR_COLOR) {
            // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
            // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
            // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
            } else {
              //IDK MAN IDK MAN IDK MAN IDK MAN IDK MAN
              //THROW IT ALL OUT
            }
          } else {
            // INTAKE INTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKEINTAKE
            // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
            // DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE DISPOSE
          }
        }
      }
      break;
    case 2:
      if (!bot.empty()) {

      } else {
        // PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP PICK UP 
        // PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
      }
      break;
    case 1:
      // WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH WE MIGHT DO SMTH
      break;
    default:
      break;
  }
}