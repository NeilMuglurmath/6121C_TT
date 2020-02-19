#include "main.h"

MotorGroup intake({PORT_INTAKE_LEFT, PORT_INTAKE_RIGHT});

void intakeIn()
{
	intake.moveVoltage(12000);
}
void intakeStop()
{
	if (isTrayGoingOut())
	{
		intake.moveVoltage(0);
		intake.setBrakeMode(AbstractMotor::brakeMode::coast);
	}
	else
	{
		intake.moveVelocity(0);
		intake.setBrakeMode(AbstractMotor::brakeMode::hold);
	}
}

void intakeStopAuto()
{
	intake.moveVoltage(0);
	intake.setBrakeMode(AbstractMotor::brakeMode::coast);
}

void intakeMove(int degrees)
{
	intake.moveRelative(degrees, 200);
}

void intakeInAuto()
{
	intake.moveVoltage(12000);
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
		intakeStop();
	}
}

void _intakeTask(void *param)
{
	while (true)
	{
		if (!isExpanding())
		{
			intakeOpControl();
		}
		pros::delay(20);
	}
}

void intakeInit()
{
	std::string taskName("Intake");
	pros::Task intake_task(_intakeTask, &taskName, "");
}