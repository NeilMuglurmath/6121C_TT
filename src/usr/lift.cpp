#include "main.h"

Motor motorLift(PORT_LIFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

pros::ADIDigitalIn liftLimitSwitch(PORT_LIFT_LIMIT_SWITCH);

const int LIFT_DOWN = 0;
const int LIFT_SMALL_TOWER = 440;
const int LIFT_SMALL_TOWER_DESCORE = 390;
const int LIFT_UPPER_LIMIT = 586;
const int LIFT_TWO_STACK = 135;
const int LIFT_FOUR_STACK = 400;
const int LIFT_CUBE_MOVE_MAX = 300;
const int LIFT_MOVE_UP_FROM_TARE = 4;

const int INTAKE_CUBE_OUT_DIST = -300;
const int INTAKE_CUBE_OUT_VEL = 80;

const double LIFT_KP = 35;
const double LIFT_KI = 0;
const double LIFT_KD = 0;

const int LIFT_THRESHOLD_ERROR = 50;
const int LIFT_MIN_VEL = 30;

int liftTarget = 0;
static double liftSpeed = 0;
double liftError = 0;
double liftPosition = 0;
double liftPIDOutput = 0;

const int LIFT_ACCEL = 850;
const int LIFT_DECEL = 800;

const int LIFT_MAX_VOLTAGE = 12000;
const int LIFT_MIN_VOLTAGE = 4000;

bool liftGoingDown = false;
bool isLiftDoingSomething = false;
bool liftHitDown = false;
bool liftPaused = false;
bool liftForceDown = false;

bool _isLiftDown()
{
	return liftLimitSwitch.get_value() == 1;
}

double liftGetPosition()
{
	return motorLift.getPosition();
}

bool liftIsDoingSomething()
{
	return isLiftDoingSomething;
}

void _liftPower(int voltage)
{
	motorLift.moveVoltage(voltage);
	motorLift.setBrakeMode(AbstractMotor::brakeMode::coast);
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
	printf("Pos: %.1f Target Pos: %.1f, Error: %.1f Speed: %.1f PID Output: %.1f lift down: %d, power drawn: %.1f \n", liftPosition, liftTarget, liftError, liftSpeed, liftPIDOutput, _isLiftDown(), motorLift.getPower());
}

void _liftPID(void *param)
{
	while (true)
	{
		if (!liftPaused)
		{
			if (liftForceDown)
			{
				int counter = 0;
				while (!_isLiftDown())
				{
					_liftPower(-LIFT_MAX_VOLTAGE);
					counter += 20;
					if (counter > 2000)
					{
						break;
					}
					pros::delay(20);
				}
				pros::delay(300);
				motorLift.tarePosition();
				motorLift.moveAbsolute(LIFT_MOVE_UP_FROM_TARE, 200);
				pros::delay(300);
				motorLift.tarePosition();
				liftDown();
				liftForceDown = false;
			}
			else
			{
				motorLift.moveAbsolute(liftTarget, 200);
			}
		}

		else
		{
			motorLift.moveVoltage(0);
		}
		pros::delay(20);
	}
}

void _liftOpControl()
{
	if (master.getDigital(ControllerDigital::up))
	{
		liftMidTower();
		moveCubeOut();
	}
	else if (master.getDigital(ControllerDigital::down))
	{
		liftDown();
	}
	else if (master.getDigital(ControllerDigital::right))
	{
		liftSmallTower();
		moveCubeOut();
	}
	else if (master.getDigital(ControllerDigital::left))
	{
		_liftSetTarget(LIFT_SMALL_TOWER_DESCORE);
	}
	else if (master.getDigital(ControllerDigital::A))
	{
		expand();
	}
}

void liftGetTwoStack()
{
	isLiftDoingSomething = true;
	_liftSetTarget(LIFT_TWO_STACK);
	intakeIn();
	while (master.getDigital(ControllerDigital::L1))
	{
		intakeIn();
		pros::delay(20);
	}
	liftDown();
	pros::delay(400);
	isLiftDoingSomething = false;
}

void liftGetFourStack()
{
	isLiftDoingSomething = true;
	_liftSetTarget(LIFT_FOUR_STACK);
	intakeIn();
	while (master.getDigital(ControllerDigital::L1))
	{
		intakeIn();
		pros::delay(20);
	}
	liftDown();
	pros::delay(400);
	isLiftDoingSomething = false;
}

void moveCubeOut()
{
	if (motorLift.getPosition() < LIFT_CUBE_MOVE_MAX)
	{
		isLiftDoingSomething = true;
		intakeMove(INTAKE_CUBE_OUT_DIST, INTAKE_CUBE_OUT_VEL);
		pros::delay(500);
		isLiftDoingSomething = false;
	}
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
	std::string task_name("Lift PID");
	pros::Task liftSmoothTask(_liftPID, &task_name, "");
}

void liftOpControlInit()
{
	std::string task_name("Lift Op");
	pros::Task lift_op_control(_liftOpControlTask, &lift_op_control, "");
}

void liftDownHard()
{
	liftForceDown = true;
	_liftSetTarget(LIFT_DOWN);
}

void expand()
{
	isLiftDoingSomething = true;
	liftMidTower();
	pros::delay(200);
	intakePower(-12000);
	pros::delay(500);
	liftPaused = true;
	pros::delay(250);
	liftPaused = false;
	// liftDownHard();
	liftDown();
	intakeIn();
	pros::delay(500);
	isLiftDoingSomething = false;
}