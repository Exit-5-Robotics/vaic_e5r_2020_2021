#include "vex.h"

using namespace vex;

void red_isolation() {
  goTo( 40, -40, 135);
  
  // void goTo( float dest_x, float dest_y, float dest_heading ) {   
  // (x, -y) ball, then (x, 0) ball, then (x, y) ball if time permits
}

void blue_isolation() {
  // (-x, y) ball, then (-x, 0) ball, then (-x, -y) ball if time permits
}