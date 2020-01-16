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
    chassisGeneratePath(46_in, -23_in, 0_deg, "go to second row");
    chassisWaitUntilSettled();
    chassisExecutePath("go to second row", true, true);
    chassisGenerateSlowStraightPath(44_in, "gather 4 cubes", 0.6);
    chassisWaitUntilSettled();
    chassisExecutePath("gather 4 cubes", true, false);
    chassisGenerateStraightPath(30_in, "go to stack");
    chassisWaitUntilSettled();
    chassisExecutePath("go to stack", true, true);
    chassisGenerateTurnPath(4.5_in, "turn to stack");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to stack", true, false);
    intakePower(-2000);
    chassisGenerateStraightPath(15_in, "deploy stack");
    pros::delay(500);
    intakeOff();
    chassisTurnWaitUntilSettled();
    chassisExecutePath("deploy stack", true, false);
    anglerOut();
    chassisGenerateSlowStraightPath(20_in, "back from stack", 0.3);
    chassisWaitUntilSettled();
    chassisExecutePath("back from stack", true, true);
    intakePower(-7000);
    anglerIn();
    chassisWaitUntilSettled();
}