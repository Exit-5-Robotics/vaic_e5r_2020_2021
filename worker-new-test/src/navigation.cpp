/*
order of tower checking):
0. end isolation facing center lines
-----
1. line up to tower1
2. check tower1
3. check tower0
4. line up to tower1
5. check tower2
6. spin to face ctower3
7. check tower3
8. spin to line up to tower1
9. repeat
(maybe turn to walls & use jetson to check for y position occasionally?)
(ballScout after each cycle?)
*/

int currentTower = 0; //current tower we fixing
bool ballNeeded; // do we need another ball to fix a tower?
bool haveAnotherBall; //if we are currently storing an additional ball of out color