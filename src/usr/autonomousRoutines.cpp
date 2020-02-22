#include "main.h"

void testProfiling()
{
    chassisGenerateStraightPath(5_in, "t");
    trayOutMediumSpeed();
    trayWaitUntilSettled();
    chassisExecutePath("t", false, false, false);
}

void progSkills()
{
    trayIn();
    chassisGenerateSlowStraightPath(44_in, "gather 4 cubes", 0.8);
    // expand();
    intakeIn();
    chassisExecutePath("gather 4 cubes", true, false, false);
    chassisGeneratePath(47_in, -25_in, 0_deg, "go to second row");
    chassisWaitUntilSettled();
    chassisExecutePath("go to second row", true, true, false);
    chassisGenerateSlowStraightPath(47_in, "gather 4 more cubes", 0.5);
    chassisWaitUntilSettled();
    chassisExecutePath("gather 4 more cubes", true, false, false);
    chassisGenerateStraightPath(34_in, "go to stack");
    chassisWaitUntilSettled();
    chassisExecutePath("go to stack", true, true, false);
    chassisGenerateTurnPath(5.9_in, "turn to stack"); //5.8
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to stack", true, false, false);
    chassisGenerateSlowStraightPath(14_in, "deploy stack", 0.9);
    lowerCubesInTray();
    intakeStop();
    chassisTurnWaitUntilSettled();
    chassisExecutePath("deploy stack", true, false, false);
    chassisGenerateStraightPath(25_in, "back away from zone");
    chassisWaitUntilSettled();
    intakeStopAuto();
    trayOutSlow();
    trayWaitUntilSettled();
    chassisExecutePath("back away from zone", true, true, false);
    chassisGenerateTurnPath(6.2_in, "turn to first tower");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to first tower", true, true, true);
    chassisGenerateStraightPath(29_in, "align to wall");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("align to wall", true, true, false);
    chassisGenerateSlowStraightPath(48_in, "get tower cube", 0.7);
    chassisWaitUntilSettled();
    chassisExecutePath("get tower cube", true, false, false);
    pros::delay(200);
    trayIn();
    pros::delay(1200);
    intakePower(8000);
    chassisGenerateStraightPath(12_in, "back from tower cube");
    chassisWaitUntilSettled();
    pros::delay(500);
    chassisExecutePath("back from tower cube", true, true, false);
    pros::delay(500);
    liftSmallTower();
    moveCubeOut();
    chassisGenerateStraightPath(14_in, "put cube in tower");
    chassisWaitUntilSettled();
    chassisExecutePath("put cube in tower", true, false, false);
    chassisGenerateStraightPath(13_in, "back from first tower");
    chassisWaitUntilSettled();
    intakePower(-6000);
    pros::delay(450);
    chassisExecutePath("back from first tower", true, true, false);
    chassisGenerateTurnPath(4.5_in, "turn to cubes"); //4.6
    chassisWaitUntilSettled();
    liftDown();
    intakePower(9000);
    chassisExecuteTurnPath("turn to cubes", true, true, false);
    chassisGenerateStraightPath(35_in, "get second cube");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("get second cube", true, false, false);
    chassisGenerateStraightPath(45_in, "go to second tower");
    chassisWaitUntilSettled();
    chassisExecutePath("go to second tower", true, true, false);
    chassisGenerateTurnPath(7.6_in, "turn to tower"); //7.6
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to tower", true, true, false);
    liftSmallTower();
    moveCubeOut();
    chassisGenerateStraightPath(14_in, "put cube in tower");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("put cube in tower", true, false, false);
    chassisGenerateSlowStraightPath(13_in, "back from 2 tower", 0.7);
    chassisWaitUntilSettled();
    intakePower(-4000);
    chassisExecutePath("back from 2 tower", true, true, false);
    chassisGenerateTurnPath(4_in, "turn to 3 tower 1");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to 3 tower 1", true, false, false);
    liftDown();
    chassisGenerateStraightPath(19_in, "go to 3 tower 1");
    chassisTurnWaitUntilSettled();
    chassisExecutePath("go to 3 tower 1", true, false, false);
    chassisGenerateTurnPath(3.7_in, "turn to 3 tower 2");
    chassisWaitUntilSettled();
    chassisExecuteTurnPath("turn to 3 tower 2", true, false, false);
    chassisGenerateSlowStraightPath(27_in, "go to 3 tower 2", 0.7);
    chassisTurnWaitUntilSettled();
    chassisExecutePath("go to 3 tower 2", true, false, false);
    intakePower(9000);
    chassisGenerateStraightPath(12_in, "back from tower cube");
    chassisWaitUntilSettled();
    pros::delay(500);
    chassisExecutePath("back from tower cube", true, true, false);
    pros::delay(500);
    liftMidTower();
    moveCubeOut();
    chassisGenerateStraightPath(20_in, "go to tower");
    chassisWaitUntilSettled();
    chassisExecutePath("go to tower", true, false, false);
    chassisWaitUntilSettled();
    intakePower(-6000);
}

void unprotected(bool blue)
{
    if (blue)
    {
        trayIn();
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
        intakeStopAuto();
        trayOutMediumSpeed();
        trayWaitUntilSettled();
        chassisExecutePath("back from zone", true, true, false);
        chassisWaitUntilSettled();
    }
    else
    {
        trayIn();
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
        intakeStopAuto();
        trayOutMediumSpeed();
        trayWaitUntilSettled();
        chassisExecutePath("back from zone", true, true, false);
        chassisWaitUntilSettled();
    }
}

void protectedSide(bool blue)
{
    if (blue)
    {
        trayIn();
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
        intakeStopAuto();
        chassisWaitUntilSettled();
        trayOutMediumSpeed();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        trayWaitUntilSettled();

        chassisExecutePath("back away from zone", true, true, false);
        pros::delay(300);
        trayIn();
        chassisWaitUntilSettled();
    }
    else
    {
        trayIn();
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
        intakeStopAuto();
        chassisWaitUntilSettled();
        trayOutMediumSpeed();
        chassisGenerateSlowStraightPath(24_in, "back away from zone", 0.9);
        trayWaitUntilSettled();

        chassisExecutePath("back away from zone", true, true, false);
        pros::delay(300);
        trayIn();
        chassisWaitUntilSettled();
    }
}
