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
    chassisGenerateSlowStraightPath(44_in, "gather 4 cubes", false, 0.6);
    chassisWaitUntilSettled();
    chassisExecutePath("gather 4 cubes", true, false);
    chassisGenerateStraightPath(30_in, "go to stack");
    chassisWaitUntilSettled();
    chassisExecutePath("go to stack", true, true);
    chassisWaitUntilSettled();
    pros::delay(200);
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