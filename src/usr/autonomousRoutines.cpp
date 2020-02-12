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
        chassisGenerateSlowStraightPath(23_in, "gather 4 cubes", 0.8);
        expand();
        intakeIn();
        chassisExecutePath("gather 4 cubes", true, false, blue);
        chassisGeneratePath(25_in, -24_in, 0_deg, "go to second row");
        chassisWaitUntilSettled();
        chassisExecutePath("go to second row", true, true, blue);
        chassisGenerateSlowStraightPath(45_in, "gather 4 more cubes", 0.6);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateStraightPath(31_in, "go to stack");
        chassisWaitUntilSettled();
        chassisExecutePath("go to stack", true, true, blue);
        chassisGenerateTurnPath(6.2_in, "turn to stack");
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
        chassisGenerateSlowStraightPath(23_in, "gather 2 cubes", 0.8);
        // expand();
        intakeIn();
        chassisExecutePath("gather 2 cubes", true, false, blue);
        // chassisGenerateSlowStraightPath(8_in, "gather 2 stack", 0.7);
        // chassisWaitUntilSettled();
        // chassisExecutePath("gather 2 stack", true, false, false);
        // liftSecondCube();
        // pros::delay(200);
        // liftDown();
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
        chassisGenerateTurnPath(3.7_in, "turn to third cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to third cube", true, blue, blue);
        chassisGenerateSlowStraightPath(32_in, "get third and fourth cubes", 1);
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get third and fourth cubes", true, false, false);
        chassisGenerateStraightPath(15_in, "back from tower");
        chassisWaitUntilSettled();
        chassisExecutePath("back from tower", true, true, false);
        chassisGenerateTurnPath(9.78_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(24_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        intakePower(-4500);
        pros::delay(300);
        intakeOff();
        chassisWaitUntilSettled();
        intakePower(-2000);
        anglerOut();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        intakePower(-10000);
        chassisExecutePath("back away from zone", true, true, false);
        anglerIn();
        pros::delay(300);
        chassisWaitUntilSettled();
    }
    else
    {
        chassisGenerateSlowStraightPath(14_in, "get second cube", 1.3);
        expand();
        intakeIn();
        chassisExecutePath("get second cube", true, false, blue);
        chassisGenerateTurnPath(3.7_in, "turn to third cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to third cube", true, blue, blue);
        chassisGenerateSlowStraightPath(32_in, "get third and fourth cubes", 1);
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get third and fourth cubes", true, false, false);
        chassisGenerateStraightPath(15_in, "back from tower");
        chassisWaitUntilSettled();
        chassisExecutePath("back from tower", true, true, false);
        chassisGenerateTurnPath(10.1_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(20_in, "go to stack");
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
        intakePower(-10000);
        chassisExecutePath("back away from zone", true, true, false);
        anglerIn();
        pros::delay(300);
        chassisWaitUntilSettled();
    }
}
