#include "main.h"

Motor motorAngler(PORT_ANGLER, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

const int ANGLER_OUT = -1320;
const int ANGLER_HALFWAY = -600;

void anglerOut()
{
	liftMove(120);
	int counter = 0;

	while (motorAngler.getPosition() > ANGLER_HALFWAY)
	{
		if (counter > 4000)
		{
			break;
		}
		motorAngler.moveVoltage(-12000);
		counter += 20;
		pros::delay(20);
	}
	counter = 0;
	while (motorAngler.getPosition() > ANGLER_OUT + 70)
	{
		if (counter > 3000)
		{
			break;
		}
		motorAngler.moveVoltage(-6000);
		counter += 20;
		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
}

void anglerExpand()
{
	motorAngler.moveAbsolute(1000, 100);
	pros::delay(1000);
	motorAngler.moveAbsolute(0, 100);
}

void anglerIn()
{
	while (motorAngler.getPosition() < 100)
	{
		motorAngler.moveVoltage(12000);
		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
	liftMove(-120);
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
	printf("%.1f %.1f\n", motorAngler.getPower(), motorAngler.getPosition());
}
