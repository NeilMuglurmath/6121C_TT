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
    chassisForwardSlow(46_in, "gather 4 cubes", true, 0.55);
    chassisGeneratePath(46_in, -23_in, 0_deg, "go to second row", false, false);
    chassisWaitUntilSettled();
    chassisExecutePath("go to second row", true, true);
    chassisGenerateSlowStraightPath(40_in, "gather 4 cubes", false, 0.6);
    chassisWaitUntilSettled();
    // chassisMove(-42_in, 25_in, 0_deg, "go to second row", false, false);
    // chassisForwardSlow(38_in, "gather 4 cubes", false, 0.7);
    chassisExecutePath("gather 4 cubes", true, false);
    chassisGenerateStraightPath(26_in, "back to stack");
    chassisWaitUntilSettled();
    chassisExecutePath("back to stack", true, true);
    chassisWaitUntilSettled();
    pros::delay(200);
    // chassisBackward(24_in, "back to stack", false);
    chassisTurn(4.7_in, "turn to stack", true, false);
    intakePower(-4000);
    pros::delay(500);
    intakeOff();
    turnWaitUntilSettled();
    chassisForward(16_in, "stack", false);
    anglerOut();
    intakePower(-7000);
    chassisBackwardSlow(20_in, "back from stack", true, 0.2);
    pros::delay(200);
    anglerIn();
}