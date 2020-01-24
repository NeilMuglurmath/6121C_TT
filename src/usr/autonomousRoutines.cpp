#include "main.h"

void testProfiling()
{
    expand();
    // chassisTurn(8_in, "a", false);
    // chassisBackward(20_in, "for", false);
}

void unprotected(bool blue)
{
    if (blue)
    {
        chassisGenerateSlowStraightPath(28_in, "gather 4 cubes", 0.8);
        expand();
        intakeIn();
        chassisExecutePath("gather 4 cubes", true, false, blue);
        // chassisGenerateSlowPath(27_in, -27_in, 0_deg, "go to second row", .9);
        chassisGeneratePath(28_in, -25_in, 0_deg, "go to second row");
        chassisWaitUntilSettled();
        chassisExecutePath("go to second row", true, true, blue);
        chassisGenerateSlowStraightPath(49_in, "gather 4 more cubes", 0.6);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateStraightPath(35_in, "go to stack");
        chassisWaitUntilSettled();
        chassisExecutePath("go to stack", true, true, blue);
        chassisGenerateTurnPath(6.4_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, blue, false);
        intakePower(-300);
        chassisGenerateSlowStraightPath(16_in, "deploy stack", 0.9);
        pros::delay(300);
        intakeOff();
        chassisTurnWaitUntilSettled();
        chassisExecutePath("deploy stack", true, false, blue);
        intakePower(-800);
        anglerOut();
        chassisGenerateSlowStraightPath(12_in, "back away from zone", 0.9);
        pros::delay(200);
        intakePower(-10000);
        chassisExecutePath("back away from zone", true, true, false);
        anglerIn();
        chassisWaitUntilSettled();
    }
    else
    {
        chassisGenerateSlowStraightPath(28_in, "gather 4 cubes", 0.8);
        expand();
        intakeIn();
        chassisExecutePath("gather 4 cubes", true, false, blue);
        // chassisGenerateSlowPath(27_in, -27_in, 0_deg, "go to second row", .9);
        chassisGeneratePath(27_in, -33_in, 0_deg, "go to second row");
        chassisWaitUntilSettled();
        chassisExecutePath("go to second row", true, true, blue);
        chassisGenerateSlowStraightPath(49_in, "gather 4 more cubes", 0.6);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateStraightPath(35_in, "go to stack");
        chassisWaitUntilSettled();
        chassisExecutePath("go to stack", true, true, blue);
        chassisGenerateTurnPath(5.75_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, blue, false);
        intakePower(-300);
        chassisGenerateSlowStraightPath(16_in, "deploy stack", 0.9);
        pros::delay(300);
        intakeOff();
        chassisTurnWaitUntilSettled();
        chassisExecutePath("deploy stack", true, false, blue);
        intakePower(-800);
        anglerOut();
        chassisGenerateSlowStraightPath(12_in, "back away from zone", 0.9);
        pros::delay(200);
        intakePower(-10000);
        chassisExecutePath("back away from zone", true, true, false);
        anglerIn();
        chassisWaitUntilSettled();
    }
}

void protectedSide(bool blue)
{
    if (blue)
    {
        chassisGenerateSlowStraightPath(14_in, "get second cube", 1.3);
        expand();
        intakeIn();
        chassisExecutePath("get second cube", true, false, blue);
        chassisGenerateTurnPath(3.75_in, "turn to third cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to third cube", true, blue, blue);
        chassisGenerateSlowStraightPath(32_in, "get third and fourth cubes", 1);
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get third and fourth cubes", true, false, false);
        chassisGenerateStraightPath(15_in, "back from tower");
        chassisWaitUntilSettled();
        chassisExecutePath("back from tower", true, true, false);
        chassisGenerateTurnPath(9.75_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(22_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        intakePower(-4500);
        pros::delay(300);
        intakeOff();
        chassisWaitUntilSettled();
        intakePower(-2000);
        anglerOut();
        pros::delay(200);
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);

        intakePower(-10000);
        chassisExecutePath("back away from zone", true, true, false);
        anglerIn();
        chassisWaitUntilSettled();
    }
    else
    {
        chassisGenerateSlowStraightPath(14_in, "get second cube", 1.3);
        expand();
        intakeIn();
        chassisExecutePath("get second cube", true, false, blue);
        chassisGenerateTurnPath(3.2_in, "turn to third cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to third cube", true, blue, blue);
        chassisGenerateSlowStraightPath(32_in, "get third and fourth cubes", 1);
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get third and fourth cubes", true, false, false);
        chassisGenerateStraightPath(15_in, "back from tower");
        chassisWaitUntilSettled();
        chassisExecutePath("back from tower", true, true, false);
        chassisGenerateTurnPath(9.6_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(24_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        intakePower(-4500);
        pros::delay(300);
        intakeOff();
        chassisGenerateStraightPath(19_in, "back away from zone");
        chassisWaitUntilSettled();
        intakePower(-2000);
        anglerOut();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        pros::delay(200);
        intakePower(-10000);
        chassisExecutePath("back away from zone", true, true, false);
        anglerIn();
        chassisWaitUntilSettled();
    }
}
