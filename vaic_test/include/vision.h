/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature SIG_ORANGE = vex::vision::signature (1, 8069, 10123, 9096, -3099, -2289, -2694, 4.1, 0);
vex::vision::signature SIG_GREEN = vex::vision::signature (2, -8641, -4479, -6560, -5279, -1727, -3502, 1.4, 0);
vex::vision::signature SIG_PURPLE = vex::vision::signature (3, 799, 2171, 1484, 6803, 9777, 8290, 3.3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT14, 50, SIG_ORANGE, SIG_GREEN, SIG_PURPLE, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/