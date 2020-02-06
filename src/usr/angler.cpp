#include "main.h"

Motor motorAngler(PORT_ANGLER, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

pros::ADIAnalogIn leftLineTracker(PORT_LEFT_LINE_TRACKER);
pros::ADIAnalogIn rightLineTracker(PORT_RIGHT_LINE_TRACKER);

const int ANGLER_OUT = -1340;
const int ANGLER_HALFWAY = -600;
const int ANGLER_LOWER_TO = -130;

const int CUBE_THRESHOLD = 2650;

bool anglerGoingOut = false;

bool isAnglerGoingOut()
{
	return anglerGoingOut;
}

bool cubeIsInRollers()
{
	return rightLineTracker.get_value() < CUBE_THRESHOLD;
}

void anglerOut()
{
	while (!cubeIsInRollers())
	{
		intakePower(-12000);
		if (master.getDigital(ControllerDigital::B))
		{
			break;
		}
	}
	intakeOff();
	int counter = 0;
	while (motorAngler.getPosition() > ANGLER_HALFWAY)
	{
		if (counter > 4000)
		{
			break;
		}

		if (master.getDigital(ControllerDigital::R1))
		{
			break;
		}

		motorAngler.moveVoltage(-12000);
		counter += 20;
		pros::delay(20);
	}
	counter = 0;
	anglerGoingOut = true;
	while (motorAngler.getPosition() > ANGLER_OUT)
	{
		if (counter > 2000)
		{
			break;
		}
		if (master.getDigital(ControllerDigital::R1))
		{
			break;
		}
		counter += 20;
		motorAngler.moveVoltage(-12000);
		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
}

void anglerOutHalfway()
{
	motorAngler.moveAbsolute(ANGLER_HALFWAY, 60);
}

void anglerIn()
{

	while (motorAngler.getPosition() < ANGLER_LOWER_TO)
	{
		motorAngler.moveVoltage(12000);
		if (master.getDigital(ControllerDigital::R2))
		{
			break;
		}

		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
	anglerGoingOut = false;
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
	else
	{

		motorAngler.moveVoltage(0);
	}
	// printf("%.1f %.1f %d %d %d\n", motorAngler.getPower(), motorAngler.getPosition(), leftLineTracker.get_value(), rightLineTracker.get_value(), cubeIsInRollers());
}
