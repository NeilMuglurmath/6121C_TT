#include "main.h"

void testProfiling()
{
    expand();
    // chassisTurn(8_in, "a", false);
    // chassisBackward(20_in, "for", false);
}

void redRight8Cube()
{
    intakeIn();
    liftHoldDown();
    chassisForwardSlow(46_in, "gather 4 cubes", true, 0.6);
    chassisGeneratePath(44_in, -23_in, 0_deg, "go to second row", false, false);
    chassisWaitUntilSettled();
    chassisExecutePath("go to second row", true, true);
    chassisGenerateSlowStraightPath(38_in, "gather 4 cubes", false, 0.45);
    chassisWaitUntilSettled();
    // chassisMove(-42_in, 25_in, 0_deg, "go to second row", false, false);
    // chassisForwardSlow(38_in, "gather 4 cubes", false, 0.7);
    chassisExecutePath("gather 4 cubes", true, false);
    chassisGenerateStraightPath(24_in, "back to stack");
    chassisWaitUntilSettled();
    chassisExecutePath("back to stack", true, true);
    chassisWaitUntilSettled();
    // chassisBackward(24_in, "back to stack", false);
    chassisTurn(5.75_in, "turn to stack", false, false);
    intakeOutSlow();
    pros::delay(500);
    intakeOff();
    chassisForward(20_in, "stack", false);
    anglerOut();
    intakeOutSlow();
    chassisBackwardSlow(20_in, "back from stack", true, 0.5);
    pros::delay(200);
    anglerIn();
}