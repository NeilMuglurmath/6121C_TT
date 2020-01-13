#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

const int LIFT_LOWER_LIMIT = 0;
const int LIFT_UPPER_LIMIT = 1622;

void liftHoldDown()
{
	if (motorLift.getPosition() < 100)
	{
		motorLift.moveVelocity(-1);
		motorLift.setBrakeMode(AbstractMotor::brakeMode::hold);
	}
	else
	{
		motorLift.moveVelocity(0);
		motorLift.setBrakeMode(AbstractMotor::brakeMode::hold);
	}
}

void liftMove(double degrees)
{
	motorLift.moveRelative(degrees, 200);
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
		// motorLift.moveVoltage(0);
	}
}

void liftPrintInfo()
{
	printf("Pos: %.1f Target Pos: %.1f, Efficiency: %.1f\n", motorLift.getPosition(), motorLift.getTargetPosition(), motorLift.getEfficiency());
}

void expand()
{
	motorLift.moveAbsolute(600, 200);
	pros::delay(800);
	motorLift.moveAbsolute(0, 200);
}