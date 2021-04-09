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

float round(float var) {
    float value = (int)(var * 100 + .5); 
    return (float)value / 100;
}

void cache_goals( void ) {
  // move out
  static MAP_RECORD  local_map;
  jetson_comms.get_data( &local_map );

  int opponentScored[9];

  int mapnum = local_map.mapnum;
  if (mapnum > 0) {
    for (int i=0; i<mapnum; i++) {
      if (local_map.mapobj[i].positionZ / 25.4 > 100000 /*REPLACE*/ && local_map.mapobj[i].classID == OTHER_COLOR) {
        // opponentScored 
        // const int prevToFind = 10;
        // auto findResult = std::find_if(std::begin(table), std::end(table), [&](const std::pair<int, struct_t*> &pair)
        // {
        //     return pair.second->prev == prevToFind;
        // });

        // int foundKey = 0; // You might want to initialise this to a value you know is invalid in your map
        // struct_t *foundValue = nullptr
        // if (findResult != std::end(table))
        // {
        //     foundKey = findResult->first;
        //     foundValue = findResult->second;

        //     // Now do something with the key or value!
        // }
      }
    }
  }

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