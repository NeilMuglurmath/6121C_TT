#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

const int LIFT_LOWER_LIMIT = 0;
const int LIFT_SMALL_TOWER = 1000;
const int LIFT_SMALL_TOWER_DESCORE = 900;
const int LIFT_UPPER_LIMIT = 1270;
const int FIRST_CUBE = 90;

const double LIFT_KP = 0.0015;
const double LIFT_KI = 0;
const double LIFT_KD = 0;

auto liftController = AsyncPosControllerBuilder()
						  .withMotor(PORT_LIFT)
						  .withGains({LIFT_KP, LIFT_KI, LIFT_KD})
						  .build();

void liftHoldDown()
{

	motorLift.moveVelocity(0);
	motorLift.setBrakeMode(AbstractMotor::brakeMode::hold);
}

double liftGetPosition()
{
	return motorLift.getPosition();
}

void liftDown()
{

	if (liftController->getTarget() != LIFT_LOWER_LIMIT)
	{
		while (motorLift.getPosition() > 20)
		{
			liftController->controllerSet(-1);
		}

		liftController->setTarget(0);
	}
}

void liftSmallTower()
{
	liftController->setTarget(LIFT_SMALL_TOWER);
}

void liftHighTower()
{
	liftController->setTarget(LIFT_UPPER_LIMIT);
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
	if (master.getDigital(ControllerDigital::up))
	{
		liftHighTower();
	}
	else if (master.getDigital(ControllerDigital::down))
	{
		liftDown();
	}
	else if (master.getDigital(ControllerDigital::right))
	{
		liftSmallTower();
	}
	else if (master.getDigital(ControllerDigital::left))
	{
		liftController->setTarget(LIFT_SMALL_TOWER_DESCORE);
	}
	else if (master.getDigital(ControllerDigital::A))
	{
		expand();
	}
	else if (master.getDigital(ControllerDigital::X))
	{
		liftController->setTarget(FIRST_CUBE);
	}
}

void liftPrintInfo()
{
	printf("Pos: %.1f Target Pos: %.1f, Efficiency: %.1f\n", motorLift.getPosition(), motorLift.getTargetPosition(), motorLift.getEfficiency());
}

void expand()
{
	liftHighTower();
	intakePower(-2000);
	// chassisMoveVoltage(-3000);
	pros::delay(1300);
	liftDown();
}