#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::red);

const int LIFT_LOWER_LIMIT = 0;
const int LIFT_UPPER_LIMIT = 390;

void liftHoldDown()
{
	motorLift.moveVelocity(0);
	motorLift.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void liftMove(double degrees)
{
	motorLift.moveRelative(degrees, 100);
}

void liftPower(int voltage)
{
	motorLift.setBrakeMode(AbstractMotor::brakeMode::coast);
	motorLift.moveVoltage(voltage);
}

bool _liftBelowTop()
{
	return motorLift.getPosition() <= LIFT_UPPER_LIMIT;
}

bool _liftAboveBottom()
{
	return motorLift.getPosition() >= LIFT_LOWER_LIMIT;
}

void liftOpControl()
{
	if (master.getDigital(ControllerDigital::up) && _liftBelowTop())

	{
		liftPower(12000);
	}
	else if (master.getDigital(ControllerDigital::down) && _liftAboveBottom())
	{
		liftPower(-12000);
	}
	else if (master.getDigital(ControllerDigital::A))
	{
		expand();
	}

	else
	{
		liftHoldDown();
	}
	// printf("%.1f %.1f\n", motorLift.getPosition(), motorLift.getPower());
}

void expand()
{
	motorLift.moveAbsolute(LIFT_UPPER_LIMIT, 100);
	pros::delay(900);
	motorLift.moveAbsolute(LIFT_LOWER_LIMIT, 100);
	pros::delay(700);
	anglerExpand();
}