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
    chassisForwardSlow(42_in, "get first few cubes", true, 0.6);
    chassisGenerateTurnPath(1_in, "turn to tower cube");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to tower cube", true, false);
    chassisGenerateStraightPath(8_in, "get tower cube");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("get tower cube", true, false);
    chassisGenerateTurnPath(3.5_in, "turn to second stack");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to second stack", true, false);
    chassisGenerateStraightPath(6_in, "move to second stack");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("move to second stack", true, false);
    chassisGenerateStraightPath(32_in, "gather second stack");
    chassisWaitUntilSettled();
    chassisExecutePath("gather second stack", true, false);
    chassisWaitUntilSettled();
}