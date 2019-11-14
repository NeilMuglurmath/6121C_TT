#include "main.h"

Motor motorAngler(PORT_ANGLER, true, AbstractMotor::gearset::red);

const int ANGLER_OUT = 1300;
const int ANGLER_HALFWAY = 900;

void anglerOut()
{
	// liftMove(40);
	int counter = 0;

	while (motorAngler.getPosition() < ANGLER_HALFWAY)
	{
		if (counter > 4000)
		{
			break;
		}
		motorAngler.move(127);
		counter += 20;
		pros::delay(20);
	}
	counter = 0;
	while (motorAngler.getPosition() < ANGLER_OUT)
	{
		if (counter > 4000)
		{
			break;
		}
		motorAngler.move(60);
		counter += 20;
		pros::delay(20);
	}
	motorAngler.move(0);
}

void anglerExpand()
{
	motorAngler.moveAbsolute(1000, 100);
	pros::delay(1000);
	motorAngler.moveAbsolute(0, 100);
}

void anglerIn()
{
	while (motorAngler.getPosition() > 100)
	{
		motorAngler.move(-127);
		pros::delay(20);
	}
	motorAngler.move(0);
	// liftMove(-40);
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