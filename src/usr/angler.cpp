#include "main.h"

Motor motorAngler(PORT_ANGLER, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

pros::ADIAnalogIn leftLineTracker(PORT_LEFT_LINE_TRACKER);
pros::ADIAnalogIn rightLineTracker(PORT_RIGHT_LINE_TRACKER);

const int ANGLER_OUT = 699;
const int ANGLER_HALFWAY = 360;
const int TURN_OFF_ROLLERS = 350;
const int ANGLER_THREE_FOURTHS = 650;
const int ANGLER_LOWER_TO = 130;

const int ANGLER_FAST_VOLTAGE = 12000;
const int ANGLER_SLOW_VOLTAGE = 3700;

const int CUBE_THRESHOLD = 2750;

bool anglerGoingOut = false;

static int traySpeed = 0;

const int TRAY_ACCEL = 50;
const int TRAY_DECEL = 220;

bool isAnglerGoingOut()
{
	return anglerGoingOut;
}

bool cubeIsInRollers()
{
	return rightLineTracker.get_value() < CUBE_THRESHOLD && rightLineTracker.get_value() > 200 || leftLineTracker.get_value() < CUBE_THRESHOLD && leftLineTracker.get_value() > 200;
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

	motorAngler.moveVoltage(traySpeed);
}

void lowerCubesInTray()
{
	if (!cubeIsInRollers())
	{
		while (!cubeIsInRollers())
		{
			intakePower(-6000);
			if (master.getDigital(ControllerDigital::L1))
			{
				break;
			}
		}
		intakePower(-6000);
		pros::delay(200);
		intakeOff();
	}
}

void anglerOut()
{

	intakeOff();
	int counter = 0;
	while (motorAngler.getPosition() < ANGLER_HALFWAY)
	{
		if (counter > 4000)
		{
			break;
		}
		if (motorAngler.getPosition() > TURN_OFF_ROLLERS)
		{
			anglerGoingOut = true;
		}

		if (master.getDigital(ControllerDigital::R1))
		{
			break;
		}

		motorAngler.moveVoltage(ANGLER_FAST_VOLTAGE);
		traySpeed = ANGLER_FAST_VOLTAGE;
		counter += 20;
		pros::delay(20);
	}
	counter = 0;
	// while (motorAngler.getPosition() < ANGLER_THREE_FOURTHS)
	// {
	// 	if (counter > 2000)
	// 	{
	// 		break;
	// 	}
	// 	if (master.getDigital(ControllerDigital::R1))
	// 	{
	// 		break;
	// 	}
	// 	counter += 20;
	// 	motorAngler.moveVoltage(6000);
	// 	pros::delay(20);
	// }
	while (motorAngler.getPosition() < ANGLER_OUT)
	{

		if (master.getDigital(ControllerDigital::R1))
		{
			break;
		}
		_traySlew(ANGLER_SLOW_VOLTAGE);
		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
}

void anglerIn()
{

	while (motorAngler.getPosition() > ANGLER_LOWER_TO)
	{
		motorAngler.moveVoltage(-12000);
		if (master.getDigital(ControllerDigital::R2))
		{
			break;
		}

		pros::delay(20);
	}
	motorAngler.moveVoltage(0);
	anglerGoingOut = false;
}

void _anglerPrintInfo()
{
	printf("Power Drawn: %.1f Position: %.1f Left Tracker: %d Right Tracker: %d Cube In Rollers: %d Tray Speed: %d\n", motorAngler.getPower(), motorAngler.getPosition(), leftLineTracker.get_value(), rightLineTracker.get_value(), cubeIsInRollers(), traySpeed);
}

void anglerOpControl()
{
	if (master.getDigital(ControllerDigital::R2))
	{
		anglerOut();
	}
	else if (master.getDigital(ControllerDigital::R1))
	{
		anglerIn();
	}
	else if (master.getDigital(ControllerDigital::B))
	{
		lowerCubesInTray();
	}

	else
	{

		motorAngler.moveVoltage(0);
	}
	_anglerPrintInfo();
}
