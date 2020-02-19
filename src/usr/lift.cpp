#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

const int LIFT_DOWN = 0;
const int LIFT_SMALL_TOWER = 420;
const int LIFT_SMALL_TOWER_DESCORE = 370;
const int LIFT_UPPER_LIMIT = 586;

const double LIFT_KP = 45;
const double LIFT_KI = 0;
const double LIFT_KD = 0;

const int LIFT_THRESHOLD_ERROR = 50;
const int LIFT_MIN_VEL = 30;

double liftTarget = 0;
static double liftSpeed = 0;
double liftError = 0;
double liftPosition = 0;
double liftPIDOutput = 0;

const int LIFT_ACCEL = 850;
const int LIFT_DECEL = 800;

const int LIFT_MAX_VOLTAGE = 12000;
const int LIFT_MIN_VOLTAGE = 4000;

bool liftGoingDown = false;
bool expanding = false;

double
liftGetPosition()
{
	return motorLift.getPosition();
}

bool isExpanding()
{
	return expanding;
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
	liftTarget = target;
}

void liftDown()
{
	_liftSetTarget(LIFT_DOWN);
}

void liftSmallTower()
{
	_liftSetTarget(LIFT_SMALL_TOWER);
}

void liftMidTower()
{
	_liftSetTarget(LIFT_UPPER_LIMIT);
}

void _liftPrintInfo()
{
	printf("Pos: %.1f Target Pos: %.1f, Error: %.1f Speed: %.1f PID Output: %.1f\n", liftPosition, liftTarget, liftError, liftSpeed, liftPIDOutput);
}

void _liftPID(void *param)
{
	while (true)
	{
		liftPosition = int(motorLift.getPosition());
		liftError = liftTarget - liftPosition;
		if (abs(liftError) > LIFT_THRESHOLD_ERROR)
		{

			liftPIDOutput = liftError * LIFT_KP;
			if (liftPIDOutput > 0 && liftPIDOutput < LIFT_MIN_VOLTAGE)
			{
				liftPIDOutput = LIFT_MIN_VOLTAGE;
			}
			else if (liftPIDOutput < 0 && liftPIDOutput > -LIFT_MIN_VOLTAGE)
			{
				liftPIDOutput = -LIFT_MIN_VOLTAGE;
			}
			_liftSlew(liftPIDOutput);
		}
		else
		{
			motorLift.moveAbsolute(liftTarget, LIFT_MIN_VEL);
		}
		pros::delay(20);
	}
}

void _liftOpControl()
{
	if (master.getDigital(ControllerDigital::up))
	{
		liftMidTower();
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
	// _liftPrintInfo();
}

void _liftOpControlTask(void *param)
{
	while (true)
	{
		_liftOpControl();
		pros::delay(20);
	}
}

void liftPIDInit()
{
	std::string task_name("Lift Smooth");
	pros::Task liftSmoothTask(_liftPID, &task_name, "");
}

void liftOpControlInit()
{
	std::string task_name("Lift");
	pros::Task lift_op_control(_liftOpControlTask, &lift_op_control, "");
}

void expand()
{
	expanding = true;
	liftMidTower();
	pros::delay(200);
	intakePower(-12000);
	pros::delay(300);
	liftDown();
	intakeIn();
	pros::delay(500);
	expanding = false;
}