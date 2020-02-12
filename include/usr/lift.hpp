#ifndef _LIFT_HPP_
#define _LIFT_HPP_

void liftMove(double degrees);
double liftGetPosition();
void liftTaskInit();
void liftSmoothControlTaskInit();
void expand();
bool isExpanding();
void liftSecondCube();
void liftDown();
#endif