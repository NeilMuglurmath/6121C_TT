#include "main.h"

Motor motorAngler(PORT_ANGLER, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

const int ANGLER_OUT = -1450;
const int ANGLER_HALFWAY = -1000;
const int ANGLER_LOWER_TO = -130;

void anglerOut()
{
	liftMove(60);
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
	liftMove(-60);
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
	// printf("%.1f %.1f\n", motorAngler.getPower(), motorAngler.getPosition());
}
