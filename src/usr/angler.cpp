#include "main.h"

Motor motorAngler(PORT_ANGLER, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

pros::ADIAnalogIn leftLineTracker(PORT_LEFT_LINE_TRACKER);
pros::ADIAnalogIn rightLineTracker(PORT_RIGHT_LINE_TRACKER);

const int ANGLER_OUT = 788;
const int ANGLER_HALFWAY = 450;
const int TURN_OFF_ROLLERS = 350;
const int ANGLER_THREE_FOURTHS = 650;
const int ANGLER_LOWER_TO = 130;

const int ANGLER_FAST_VOLTAGE = 9000;
const int ANGLER_SLOW_VOLTAGE = 5000;

const int CUBE_THRESHOLD = 2750;

bool anglerGoingOut = false;

bool isAnglerGoingOut()
{
	return anglerGoingOut;
}

bool cubeIsInRollers()
{
	return rightLineTracker.get_value() < CUBE_THRESHOLD && rightLineTracker.get_value() > 200 || leftLineTracker.get_value() < CUBE_THRESHOLD && leftLineTracker.get_value() > 200;
}

void lowerCubesInTray()
{
	if (!cubeIsInRollers())
	{
		while (!cubeIsInRollers())
		{
			intakePower(-6000);
			if (master.getDigital(ControllerDigital::L1))
			{
				break;
			}
		}
		intakeMove(-100);
	}
}

void anglerOut()
{

	intakeOff();
	int counter = 0;
	while (motorAngler.getPosition() < ANGLER_HALFWAY)
	{
		if (counter > 4000)
		{
			break;
		}
		if (motorAngler.getPosition() > TURN_OFF_ROLLERS)
		{
			anglerGoingOut = true;
		}

		if (master.getDigital(ControllerDigital::R1))
		{
			break;
		}

		motorAngler.moveVoltage(ANGLER_FAST_VOLTAGE);
		counter += 20;
		pros::delay(20);
	}
	counter = 0;
	// while (motorAngler.getPosition() < ANGLER_THREE_FOURTHS)
	// {
	// 	if (counter > 2000)
	// 	{
	// 		break;
	// 	}
	// 	if (master.getDigital(ControllerDigital::R1))
	// 	{
	// 		break;
	// 	}
	// 	counter += 20;
	// 	motorAngler.moveVoltage(6000);
	// 	pros::delay(20);
	// }
	while (motorAngler.getPosition() < ANGLER_OUT)
	{

		if (master.getDigital(ControllerDigital::R1))
		{
			break;
		}
		motorAngler.moveVoltage(ANGLER_SLOW_VOLTAGE);
		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
}

void anglerIn()
{

	while (motorAngler.getPosition() > ANGLER_LOWER_TO)
	{
		motorAngler.moveVoltage(-12000);
		if (master.getDigital(ControllerDigital::R2))
		{
			break;
		}

		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
	anglerGoingOut = false;
}

void _anglerPrintInfo()
{
	printf("Power Drawn: %.1f Position: %.1f Left Tracker: %d Right Tracker: %d Cube In Rollers: %d\n", motorAngler.getPower(), motorAngler.getPosition(), leftLineTracker.get_value(), rightLineTracker.get_value(), cubeIsInRollers());
}

void anglerOpControl()
{
	if (master.getDigital(ControllerDigital::R2))
	{
		anglerOut();
	}
	else if (master.getDigital(ControllerDigital::R1))
	{
		anglerIn();
	}
	else if (master.getDigital(ControllerDigital::B))
	{
		lowerCubesInTray();
	}

	else
	{

		motorAngler.moveVoltage(0);
	}
	_anglerPrintInfo();
}
