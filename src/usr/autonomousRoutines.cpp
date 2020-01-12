#include "main.h"

void testProfiling()
{
    pros::lcd::print(1, "hi");
    chassisForward(20_in, false);
    chassisBackward(20_in, false);
}