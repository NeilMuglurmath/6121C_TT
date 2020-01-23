#include "main.h"

MotorGroup intake({PORT_INTAKE_LEFT, PORT_INTAKE_RIGHT});

void intakeIn()
{
	intake.moveVoltage(12000);
}
void intakeOff()
{
	intake.moveVelocity(0);
	intake.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void intakeInAuto()
{
	intake.moveVelocity(150);
}

void intakePower(int voltage)
{
	intake.moveVoltage(voltage);
}

void intakeOpControl()
{
	if (master.getDigital(ControllerDigital::L1))
	{
		intakeIn();
	}
	else if (master.getDigital(ControllerDigital::L2))
	{
		if (liftGetPosition() < 1100)
		{
			intakePower(-6000);
		}
		else
		{
			intakePower(-10000);
		}
	}

	else
	{
		intakeOff();
	}
}

void _intakeTask(void *param)
{
	while (true)
	{
		intakeOpControl();
		pros::delay(20);
	}
}

void intakeInit()
{
	std::string text("Chassis");
	pros::Task my_task(_intakeTask, &text, "");
}