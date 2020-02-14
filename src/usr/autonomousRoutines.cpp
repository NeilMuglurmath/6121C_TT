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
        chassisGenerateSlowStraightPath(23_in, "gather 2 cubes", 0.8);
        expand();
        intakeIn();
        chassisExecutePath("gather 2 cubes", true, false, blue);
        chassisGeneratePath(26_in, -23.75_in, 0_deg, "go to second row");
        chassisWaitUntilSettled();
        chassisExecutePath("go to second row", true, true, blue);
        chassisGenerateSlowStraightPath(45_in, "gather 4 more cubes", 0.5);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateStraightPath(32_in, "go to stack");
        chassisWaitUntilSettled();
        chassisExecutePath("go to stack", true, true, blue);
        chassisGenerateTurnPath(6.02_in, "turn to stack"); //5.75
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, blue, false);
        chassisGenerateStraightPath(14_in, "deploy stack");
        lowerCubesInTray();
        chassisTurnWaitUntilSettled();
        chassisExecutePath("deploy stack", true, false, blue);
        chassisGenerateSlowStraightPath(12_in, "back away from zone", 1);
        chassisWaitUntilSettled();
        intakePower(-8000);
        anglerOut();
        chassisExecutePath("back away from zone", true, true, false);
        pros::delay(400);
        anglerIn();
        chassisWaitUntilSettled();
    }
    else
    {
        chassisGenerateSlowStraightPath(23_in, "gather 2 cubes", 0.8);
        expand();
        intakeIn();
        chassisExecutePath("gather 2 cubes", true, false, blue);
        chassisGeneratePath(26_in, -24_in, 0_deg, "go to second row");
        chassisWaitUntilSettled();
        chassisExecutePath("go to second row", true, true, blue);
        chassisGenerateSlowStraightPath(45_in, "gather 4 more cubes", 0.5);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateStraightPath(32_in, "go to stack");
        chassisWaitUntilSettled();
        chassisExecutePath("go to stack", true, true, blue);
        chassisGenerateTurnPath(6.02_in, "turn to stack"); //5.75
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, blue, false);
        chassisGenerateStraightPath(14_in, "deploy stack");
        lowerCubesInTray();
        chassisTurnWaitUntilSettled();
        chassisExecutePath("deploy stack", true, false, blue);
        chassisGenerateSlowStraightPath(12_in, "back away from zone", 1);
        chassisWaitUntilSettled();
        intakePower(-8000);
        anglerOut();
        chassisExecutePath("back away from zone", true, true, false);
        pros::delay(400);
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
        chassisGenerateTurnPath(4_in, "turn to third cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to third cube", true, blue, blue);
        chassisGenerateSlowStraightPath(31_in, "get third and fourth cubes", 1);
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get third and fourth cubes", true, false, false);
        chassisGenerateStraightPath(15_in, "back from tower");
        chassisWaitUntilSettled();
        chassisExecutePath("back from tower", true, true, false);
        chassisGenerateTurnPath(9_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(22_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        lowerCubesInTray();
        chassisWaitUntilSettled();
        anglerOut();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        chassisExecutePath("back away from zone", true, true, false);
        intakePower(-6000);
        pros::delay(300);
        anglerIn();
        chassisWaitUntilSettled();
    }
    else
    {
        chassisGenerateSlowStraightPath(14_in, "get second cube", 1.3);
        expand();
        intakeIn();
        chassisExecutePath("get second cube", true, false, blue);
        chassisGenerateTurnPath(4_in, "turn to third cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to third cube", true, blue, blue);
        chassisGenerateSlowStraightPath(31_in, "get third and fourth cubes", 1);
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get third and fourth cubes", true, false, false);
        chassisGenerateStraightPath(15_in, "back from tower");
        chassisWaitUntilSettled();
        chassisExecutePath("back from tower", true, true, false);
        chassisGenerateTurnPath(9_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(22_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        lowerCubesInTray();
        chassisWaitUntilSettled();
        anglerOut();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        chassisExecutePath("back away from zone", true, true, false);
        intakePower(-6000);
        pros::delay(300);
        anglerIn();
        chassisWaitUntilSettled();
    }
}
