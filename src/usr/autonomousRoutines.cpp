#include "main.h"

void testProfiling()
{
    pros::lcd::print(1, "hi");
    chassisForward(30_in, "A");
}