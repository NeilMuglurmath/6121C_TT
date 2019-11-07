#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::red);

void liftHoldDown()
{
	motorLift.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void liftMove(double degrees)
{
	motorLift.move_relative(degrees, 100);
}

void liftPower(int voltage)
{
	motorLift.move_voltage(voltage);
}

bool liftIsUp()
{
	return motorLift.getPosition() > 100;
}

void liftOpControl()
{
	if (master.getDigital(ControllerDigital::L2))
	{
		motorLift.moveVoltage(12000);
	}
	else if (master.getDigital(ControllerDigital::down))
	{
		motorLift.moveVoltage(-12000);
	}
	else
	{

		liftHoldDown();
	}
}