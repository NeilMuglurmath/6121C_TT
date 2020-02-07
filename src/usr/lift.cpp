#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

const int LIFT_LOWER_LIMIT = 0;
const int LIFT_SMALL_TOWER = 350;
const int LIFT_SMALL_TOWER_DESCORE = 300;
const int LIFT_UPPER_LIMIT = 600;

const double LIFT_KP = 0.0001;
const double LIFT_KI = 0.004;
const double LIFT_KD = 0.000001;

int liftTarget = 0;
static int liftSpeed = 0;
int liftError = 0;

const int LIFT_ACCEL = 850;
const int LIFT_DECEL = 800;

const int LIFT_MAX_VOLTAGE = 12000;
const int LIFT_SLOW_VOLTAGE = 4000;
const int LIFT_SLOW_VELOCITY = 30;
const int LIFT_ULTRA_SLOW = 3000;
const int LIFT_DISTANCE_BEFORE_SLOW = 300;
const int LIFT_DISTANCE_BEFORE_ULTRA_SLOW = 100;
const int LIFT_SLOW_DISTANCE_MULTIPLIER = 0.5;
const int LIFT_ACIVATE_PID = 30;

bool liftGoingDown = false;

bool activatedPID = false;

double
liftGetPosition()
{
	return motorLift.getPosition();
}

void _liftPower(int voltage)
{
	motorLift.setBrakeMode(AbstractMotor::brakeMode::coast);
	motorLift.moveVoltage(voltage);
}

void _liftSlew(double liftTargetSpeed)
{
	int step;

	if (abs(liftSpeed) < abs(liftTargetSpeed))
		step = LIFT_ACCEL;
	else
		step = LIFT_DECEL;

	if (liftTargetSpeed > liftSpeed + step)
		liftSpeed += step;
	else if (liftTargetSpeed < liftSpeed - step)
		liftSpeed -= step;
	else
		liftSpeed = liftTargetSpeed;

	_liftPower(liftSpeed);
}

void _liftSetTarget(int target)
{
	liftSpeed = 0;
	activatedPID = false;
	liftTarget = target;
}

void liftDown()
{
	_liftSetTarget(LIFT_LOWER_LIMIT);
}

void liftSmallTower()
{
	_liftSetTarget(LIFT_SMALL_TOWER);
}

void liftHighTower()
{
	_liftSetTarget(LIFT_UPPER_LIMIT);
}

void liftMove(double degrees)
{
	motorLift.moveRelative(degrees, 200);
}

bool _liftBelowTop()
{
	return motorLift.getPosition() <= LIFT_UPPER_LIMIT;
}

bool _liftAboveBottom()
{
	return motorLift.getPosition() >= LIFT_LOWER_LIMIT;
}

void _liftPrintInfo()
{
	printf("Pos: %.1f Target Pos: %d, Error: %d Speed: %d\n", motorLift.getPosition(), liftTarget, liftError, liftSpeed);
}

void _liftSmoothControl(void *param)
{
	while (true)
	{
		liftError = abs(liftGetPosition() - liftTarget);
		if (liftGetPosition() < liftTarget)
		{
			liftGoingDown = false;
		}
		else if (liftGetPosition() > liftTarget)
		{
			liftGoingDown = true;
		}

		if (liftError >= LIFT_DISTANCE_BEFORE_SLOW)
		{
			_liftSlew(liftGoingDown ? -LIFT_MAX_VOLTAGE : LIFT_MAX_VOLTAGE);
		}
		else if (liftError < LIFT_DISTANCE_BEFORE_SLOW && liftError >= LIFT_DISTANCE_BEFORE_ULTRA_SLOW)
		{
			_liftSlew(liftGoingDown ? -LIFT_SLOW_VOLTAGE : LIFT_SLOW_VOLTAGE);
		}
		else if (liftError < LIFT_DISTANCE_BEFORE_ULTRA_SLOW && liftError >= LIFT_ACIVATE_PID && !activatedPID)
		{
			_liftSlew(liftGoingDown ? -LIFT_ULTRA_SLOW : LIFT_ULTRA_SLOW);
		}
		else
		{
			activatedPID = true;
			motorLift.moveAbsolute(liftTarget, LIFT_SLOW_VELOCITY);
		}

		pros::delay(20);
	}
}

void _liftOpControl()
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
		_liftSetTarget(LIFT_SMALL_TOWER_DESCORE);
	}
	else if (master.getDigital(ControllerDigital::A))
	{
		expand();
	}
	_liftPrintInfo();
}

void _liftTask(void *param)
{
	while (true)
	{
		_liftOpControl();
		pros::delay(20);
	}
}

void liftSmoothControlTaskInit()
{
	std::string taskName("Lift Smooth");
	pros::Task liftSmoothTask(_liftSmoothControl, &taskName, "");
}

void liftTaskInit()
{
	std::string text("Lift");
	pros::Task my_task(_liftTask, &text, "");
}

void expand()
{
}