#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

const int LIFT_LOWER_LIMIT = 0;
const int LIFT_SMALL_TOWER = 420;
const int LIFT_SMALL_TOWER_DESCORE = 370;
const int LIFT_UPPER_LIMIT = 586;
const int LIFT_TWO_STACK = 200;

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
bool expanding = false;
bool activatedPID = false;

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
	activatedPID = false;
	liftTarget = target;
}

void liftSecondCube()
{
	_liftSetTarget(LIFT_TWO_STACK);
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
		// if (liftTarget != LIFT_LOWER_LIMIT)
		// {
		motorLift.moveAbsolute(liftTarget, 200);
		// }
		// else
		// {
		// 	if (motorLift.getPosition() > LIFT_LOWER_LIMIT + 100)
		// 	{
		// 		motorLift.moveVoltage(-12000);
		// 	}
		// 	else
		// 	{
		// 		motorLift.moveAbsolute(LIFT_LOWER_LIMIT, 200);
		// 	}
		// }
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
	// _liftPrintInfo();
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
	expanding = true;
	liftHighTower();
	pros::delay(200);
	intakePower(-12000);
	pros::delay(300);
	liftDown();
	intakeIn();
	pros::delay(500);
	expanding = false;
}