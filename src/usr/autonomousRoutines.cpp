#include "main.h"

void testProfiling()
{
    chassisGeneratePath(-12_in, -14_in, 135_deg, "turn to stack");
    chassisExecutePath("turn to stack", true, false, false);
    chassisWaitUntilSettled();
}

void unprotected(bool blue)
{
    if (blue)
    {
        chassisGenerateStraightPath(3_in, "expand forward");
        chassisExecutePath("expand forward", true, false, false);
        expand();
        intakeInAuto();
        chassisGenerateSlowStraightPath(38_in, "gather 4 more cubes", 0.7);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateTurnPath(1.4_in, "turn to tower cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to tower cube", true, !blue, blue);
        chassisGenerateStraightPath(8_in, "get tower cube");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get tower cube", true, false, false);
        chassisGenerateTurnPath(1_in, "turn back straight");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn back straight", true, blue, blue);
        chassisGenerateStraightPath(37_in, "back to zone");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("back to zone", true, true, false);
        chassisGenerateTurnPath(6.3_in, "turn to zone");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to zone", true, blue, blue);
        lowerCubesInTray();
        chassisGenerateStraightPath(11_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        chassisGenerateStraightPath(12_in, "back from zone");
        pros::delay(500);
        chassisWaitUntilSettled();
        intakeOffAuto();
        anglerOutMediumSpeed();
        chassisExecutePath("back from zone", true, true, false);
        chassisWaitUntilSettled();
    }
    else
    {
        chassisGenerateStraightPath(3_in, "expand forward");
        chassisExecutePath("expand forward", true, false, false);
        expand();
        intakeInAuto();
        chassisGenerateSlowStraightPath(37_in, "gather 4 more cubes", 0.7);
        chassisWaitUntilSettled();
        chassisExecutePath("gather 4 more cubes", true, false, blue);
        chassisGenerateTurnPath(1.4_in, "turn to tower cube");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to tower cube", true, !blue, blue);
        chassisGenerateStraightPath(8_in, "get tower cube");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("get tower cube", true, false, false);
        chassisGenerateTurnPath(1_in, "turn back straight");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn back straight", true, blue, blue);
        chassisGenerateStraightPath(37_in, "back to zone");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("back to zone", true, true, false);
        chassisGenerateTurnPath(6.1_in, "turn to zone");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to zone", true, blue, blue);
        lowerCubesInTray();
        chassisGenerateStraightPath(11_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        chassisGenerateStraightPath(12_in, "back from zone");
        pros::delay(500);
        chassisWaitUntilSettled();
        intakeOffAuto();
        anglerOutMediumSpeed();
        chassisExecutePath("back from zone", true, true, false);
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
        chassisGenerateTurnPath(9.1_in, "turn to stack");
        chassisWaitUntilSettled();
        chassisExecuteTurnPath("turn to stack", true, !blue, blue);
        chassisGenerateStraightPath(22_in, "go to stack");
        chassisTurnWaitUntilSettled();
        chassisExecutePath("go to stack", true, false, false);
        lowerCubesInTray();
        intakeOffAuto();
        chassisWaitUntilSettled();
        anglerOutMediumSpeed();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        chassisExecutePath("back away from zone", true, true, false);
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
        intakeOffAuto();
        chassisWaitUntilSettled();
        anglerOutFast();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        chassisExecutePath("back away from zone", true, true, false);
        pros::delay(300);
        anglerIn();
        chassisWaitUntilSettled();
    }
}
