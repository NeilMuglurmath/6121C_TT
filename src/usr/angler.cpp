#include "main.h"

Motor motorAngler(PORT_ANGLER, true, AbstractMotor::gearset::red);

const int ANGLER_OUT = 1275;
const int ANGLER_HALFWAY = 750;

void anglerOut()
{
	liftMove(45);
	while (motorAngler.getPosition() < ANGLER_HALFWAY)
	{
		motorAngler.move(127);
		pros::delay(20);
	}
	while (motorAngler.getPosition() < ANGLER_OUT)
	{
		motorAngler.move(40);
		pros::delay(20);
	}
	motorAngler.move(0);
}

void anglerIn()
{
	while (motorAngler.getPosition() > 100)
	{
		motorAngler.move(-127);
		pros::delay(20);
	}
	motorAngler.move(0);
	liftMove(-45);
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
}