#include "main.h"

Motor motorTray(PORT_TRAY, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

pros::ADIAnalogIn leftLineTracker(PORT_LEFT_LINE_TRACKER);
pros::ADIAnalogIn rightLineTracker(PORT_RIGHT_LINE_TRACKER);

const int TRAY_OUT = 840;
const int TRAY_IN = 0;
const int ROLLERS_OFF = 350;

const int INTAKE_CUBE_OUT_DIST = -100;
const int INTAKE_CUBE_OUT_VEL = 40;

const double TRAY_SLOW_KP = 26;
const double TRAY_MID_KP = 28;
const double TRAY_FAST_KP = 32;

const int TRAY_MAX_VEL = 100;
const int TRAY_MIN_VEL = 17;

const int TRAY_MIN_VOLTAGE = 2800;

const int ROLLER_OUT_VOLTAGE = -4000;

const int CUBE_THRESHOLD = 2750;
const int TRACKER_MIN = 200;

const int TRAY_THRESHOLD_ERROR = 30;

bool trayGoingOut = false;

static double traySpeed = 0;

const int TRAY_ACCEL = 500;
const int TRAY_DECEL = 500;

double trayError;
double trayKP = TRAY_SLOW_KP;
double trayPIDOutput = 0;
double trayPosition = 0;
double trayTarget = 0;

bool intakeBusy = false;

bool isTrayGoingOut()
{
	return trayGoingOut;
}

bool isIntakeBusy()
{
	return intakeBusy;
}

void _traySetTarget(double target)
{
	trayTarget = target;
	traySpeed = 0;
}

bool cubeIsInRollers()
{
	return rightLineTracker.get_value() < CUBE_THRESHOLD && rightLineTracker.get_value() > TRACKER_MIN || leftLineTracker.get_value() < CUBE_THRESHOLD && leftLineTracker.get_value() > TRACKER_MIN;
}

void _traySlew(double trayTargetSpeed)
{
	int step;

	if (abs(traySpeed) < abs(trayTargetSpeed))
		step = TRAY_ACCEL;
	else
		step = TRAY_DECEL;

	if (trayTargetSpeed > traySpeed + step)
		traySpeed += step;
	else if (trayTargetSpeed < traySpeed - step)
		traySpeed -= step;
	else
		traySpeed = trayTargetSpeed;

	motorTray.moveVoltage(traySpeed);
}

void lowerCubesInTray()
{
	intakeBusy = true;
	intakeMove(INTAKE_CUBE_OUT_DIST, INTAKE_CUBE_OUT_VEL);
	pros::delay(500);
	intakeBusy = false;
}

void trayOutSlow()
{
	trayKP = TRAY_SLOW_KP;
	_traySetTarget(TRAY_OUT);
}

void trayOutMediumSpeed()
{
	trayKP = TRAY_MID_KP;
	_traySetTarget(TRAY_OUT);
}

void trayOutFast()
{
	trayKP = TRAY_FAST_KP;
	_traySetTarget(TRAY_OUT);
}

void trayIn()
{
	trayKP = TRAY_FAST_KP;
	_traySetTarget(TRAY_IN);
}

void _trayPrintInfo()
{
	printf("PID Output: %.1f Position: %.1f Left Tracker: %d Right Tracker: %d error: %.1f Tray Speed: %.1f\n", trayPIDOutput, trayPosition, leftLineTracker.get_value(), rightLineTracker.get_value(), trayError, traySpeed);
}

void _trayPID(void *param)
{
	trayError = 0;
	while (true)
	{
		trayPosition = motorTray.getPosition();
		trayError = trayTarget - trayPosition;
		if (abs(trayError) > TRAY_THRESHOLD_ERROR && trayTarget != TRAY_IN)
		{
			trayPosition = motorTray.getPosition();
			trayError = trayTarget - trayPosition;
			trayPIDOutput = trayError * trayKP;
			if (trayPIDOutput > 0 && trayPIDOutput < TRAY_MIN_VOLTAGE)
			{
				trayPIDOutput = TRAY_MIN_VOLTAGE;
			}
			else if (trayPIDOutput < 0 && trayPIDOutput > -TRAY_MIN_VOLTAGE)
			{
				trayPIDOutput = -TRAY_MIN_VOLTAGE;
			}
			motorTray.moveVoltage(trayPIDOutput);
			if (trayPosition > ROLLERS_OFF)
			{
				trayGoingOut = true;
			}
		}
		else if (trayTarget == TRAY_IN)
		{
			motorTray.moveAbsolute(trayTarget, TRAY_MAX_VEL);
			if (trayPosition < ROLLERS_OFF)
			{
				trayGoingOut = false;
			}
		}
		else
		{
			motorTray.moveAbsolute(trayTarget, TRAY_MIN_VEL);
		}
		pros::delay(20);
	}
}

void trayWaitUntilSettled()
{
	while (true)
	{
		pros::delay(20);
		if (abs(trayError) < TRAY_THRESHOLD_ERROR)
		{
			break;
		}
		pros::delay(200);
	}
}

void _trayOpControl()
{
	if (master.getDigital(ControllerDigital::R2))
	{
		trayOutSlow();
	}
	else if (master.getDigital(ControllerDigital::R1))
	{
		trayIn();
	}
	else if (master.getDigital(ControllerDigital::B))
	{
		lowerCubesInTray();
	}

	else if (master.getDigital(ControllerDigital::Y))
	{
		trayOutFast();
	}
}

void trayPIDInit()
{
	std::string taskName("tray");
	pros::Task trayTask(_trayPID, &taskName, "");
}

void _trayOpControlTask(void *param)
{
	while (true)
	{
		_trayOpControl();
		pros::delay(20);
	}
}

void trayOpControlInit()
{
	std::string task_name("Lift");
	pros::Task tray_op_control(_trayOpControlTask, &task_name, "");
}