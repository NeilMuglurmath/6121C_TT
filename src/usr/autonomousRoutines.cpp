#include "main.h"

void testProfiling()
{
    expand();
    // chassisTurn(8_in, "a", false);
    // chassisBackward(20_in, "for", false);
}

void redRight8Cube()
{
    expand();
    intakeIn();
    liftHoldDown();
    chassisForwardSlow(30_in, "gather 4 cubes", true, 0.8);
    chassisGeneratePath(31_in, -25_in, 0_deg, "go to second row");
    chassisWaitUntilSettled();
    chassisExecutePath("go to second row", true, true);
    chassisGenerateSlowStraightPath(47_in, "gather 4 more cubes", 0.6);
    chassisWaitUntilSettled();
    chassisExecutePath("gather 4 more cubes", true, false);
    chassisGenerateStraightPath(33_in, "go to stack");
    chassisWaitUntilSettled();
    chassisExecutePath("go to stack", true, true);
    chassisGenerateTurnPath(7.4_in, "turn to stack");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to stack", true, false);
    intakePower(-4300);
    chassisGenerateSlowStraightPath(16_in, "deploy stack", 0.9);
    pros::delay(300);
    intakeOff();
    chassisTurnWaitUntilSettled();
    chassisExecutePath("deploy stack", true, false);
    intakePower(-400);
    anglerOut();
    pros::delay(200);
    chassisGenerateSlowStraightPath(20_in, "back from stack", 0.25);
    chassisWaitUntilSettled();
    anglerIn();
    pros::delay(200);
    intakePower(-7000);
    chassisExecutePath("back from stack", true, true);
    chassisWaitUntilSettled();
}

void redLeft()
{
    intakeIn();
    liftHoldDown();
    chassisForward(43_in, "get first two cubes", true);
    chassisGenerateStraightPath(24_in, "back to third cube");
    chassisWaitUntilSettled();
    chassisExecutePath("back to third cube", true, true);
    chassisGenerateTurnPath(3.8_in, "turn to third cube");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to third cube", true, true);
    chassisGenerateStraightPath(24_in, "get third cube");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("get third cube", true, false);
    chassisGenerateTurnPath(1.5_in, "turn to stack");
    chassisWaitUntilSettled();
    intakeOff();
    chassisExecuteTurnPath("turn to stack", true, true);
    chassisGenerateSlowStraightPath(10_in, "deploy stack", 0.9);
    chassisTurnWaitUntilSettled();
    intakePower(-2000);
    chassisExecutePath("deploy stack", true, false);
    chassisWaitUntilSettled();
    intakePower(-2700);
    anglerOut();
    chassisGenerateSlowStraightPath(20_in, "back from stack", 0.25);
    chassisWaitUntilSettled();
    intakePower(-7000);
    chassisExecutePath("back from stack", true, true);
    anglerIn();
    chassisWaitUntilSettled();
}
