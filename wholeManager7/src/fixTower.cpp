/*  fixTower( topRobot, middleRobot, bottomRobot, topTower, middleTower, bottomTower );
    0: nothing
    1: our color
    2: not our color
*/

#include "vex.h"

using namespace vex;

/*********PREPARATION*********/

//checking if it is possible to gain possession of the tower
bool checkPossible(int bPos[]){
  
  int count = 0;
  int ballAmt = 0;
  bool isPossible = false;
  
  while(count <= 5){

    if((bPos[count] == 1) || (bPos[count] == 2)){
      ballAmt++;
      if(bPos[count] == 1){
        isPossible = true;
      }
    }

    count++;
  }

  if(ballAmt < 3){
      isPossible = false;
  }

  if(isPossible == false){
    Brain.Screen.print("Not possible");
  }

  return isPossible;
}

void setSituation(int bPos[], int situation[]){
  /*
  situation[] = {title, main, sub}
  title is decided in main
  */

  //main
  if(bPos[0] != 0){
    situation[1] = 1;
    Brain.Screen.print("main: 1");
  } else if (bPos[0] == 0){
    situation[1] = 2;
    Brain.Screen.print("main: 2");
  } else if (bPos[1] == 0){
    situation[1] = 3;
    Brain.Screen.print("main: 3");
  } else if (bPos[2] == 0){
    situation[1] = 4;
    Brain.Screen.print("main: 4");
  }

  //sub
  //lists -- {bPos[__], value}
  int sit012List[] = {0, 1, 1, 1, 2, 1, 3, 1, 4, 1};
  int sit03List[] = {1, 1, 2, 1, 3, 1, 0, 1};
  int sit04List[] = {2, 1, 1, 0, 0, 1};

  int count = 0;
  bool isFound = false;

  if((situation[0] == 1) || (situation[0] == 2)){
    while(isFound == false){
      if(bPos[sit012List[count]] == sit012List[count + 1]){
        situation[2] = (count/2 + 1) - (situation[1] - 1);
        isFound = true;
      }
      count += 2;
    }
  }
  if(situation[0] == 3){
    while(isFound == false){
      if(bPos[sit03List[count*2]] == sit03List[count*2 + 1] && (situation[1] == 1)){
        situation[2] = count + 1;
        isFound = true;
      }
      //the abs switches 0 to 1 and 1 to 0
      if((bPos[sit03List[count*2]] == abs(sit03List[count*2 + 1] - 1)) && (isFound == false) && (count > 0) && situation[1] == 2){
        situation[2] = count;
        isFound = true;
      }

      count ++;
    }
  }
  if(situation[0] == 4){
    while(isFound == false){
      if(bPos[sit04List[count]] == sit04List[count + 1]){
        situation[2] = count/2 + 1;
        isFound = true;
      }
      count += 2;
    }
  }

}

// *********DROP & INTAKE*********
void dropBall(int reps){
  //this just moves the rollers
  for(int i = 0; i < reps; i++){
    Brain.Screen.newLine();
    Brain.Screen.print("Push");
  }
}

void intakeBall(int reps){
  //this intakes and pushes until the ball is in bPos[2]
  for(int i = 0; i < reps; i++){
    Brain.Screen.newLine();
    Brain.Screen.print("Intake");
  }
}

/*********TOWERS HA HA HA*********/

void tower2(int situation[]){
  Brain.Screen.print("tower2");
  intakeBall(situation[2]);
  dropBall(situation[1] - 1);
}

void tower0(int situation[]){
  Brain.Screen.print("tower0");
  intakeBall(situation[2] - 1);
  dropBall(situation[1]);
}

void tower00(int situation[]){
  Brain.Screen.print("tower00");
  dropBall(situation[1] - 1);
  intakeBall(situation[2] - 1);
  dropBall(situation[1] - 1);
}

void tower000(int situation[]){
  Brain.Screen.print("tower000");
  dropBall(3);
  intakeBall(situation[2] - 1);
  if(situation[2] != 1){
    dropBall(3);
  }
}


void fixTower(int tRobot, int mRobot, int bRobot, int tTower, int mTower, int bTower) {
  //stores states of balls in robot & tower, will be taken from intel camera
  /*
    0: nothing
    1: our color
    2: not our color
  */
  // bPos[] = { topRobot, middleRobot, bottomRobot, topTower, middleTower, bottomTower }
  int bPos[] = {tRobot, mRobot, bRobot, tTower, mTower, bTower};
  //situation[] = {title, main, sub}
  int situation[] = {0, 0, 0};

  //continue if it's possible to do anything
  if(checkPossible(bPos)){

    //decide pathway
    if(bPos[5] == 0){
      if(bPos[4] == 0){
        if(bPos[3] == 0){
          situation[0] = 4;
          setSituation(bPos, situation);
          tower000(situation);
        }else{
          situation[0] = 3;
          setSituation(bPos, situation);
          tower00(situation);
        }
      }else{
        situation[0] = 2;
        setSituation(bPos, situation);
        tower0(situation);
      }
    }
    if(bPos[5] == 1){
      //done
    }
    if(bPos[5] == 2){
      situation[0] = 1;
      setSituation(bPos, situation);
      tower2(situation);
    }

  }

  Brain.Screen.print("Complete");
}

