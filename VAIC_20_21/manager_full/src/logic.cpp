#include "vex.h"

using namespace vex;
using namespace std;

int mapScore[3][3] = {{0, 0, 0},  // 00, 01, 02
                      {0, 0, 0},  // 10, 11, 12
                      {0, 0, 0}}; // 20, 21, 22

// hashmap??

deque<int> goalsVisiting;



float round(float var) {
    float value = (int)(var * 100 + .5); 
    return (float)value / 100;
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