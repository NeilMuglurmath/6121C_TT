#include "main.h"

Controller master;

const double MAX_VEL = 1.4;
const double MAX_ACC = 1.5;
const double MAX_JERK = 7;

QLength lastX = 0_in;
QLength lastY = 0_in;
QAngle lastTheta = 0_deg;

std::string lastPath("");
std::string lastTurnPath("");

QLength WHEELBASE_WIDTH = 10_in;
QLength WHEEL_DIAM = 1.77_in;

auto chassis = ChassisControllerBuilder()
				   .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {PORT_RIGHT_BACK, PORT_RIGHT_FRONT})
				   .withDimensions(AbstractMotor::gearset::blue, {{1.77_in, 10_in}, imev5BlueTPR})
				   .build();

auto chassisAuto = ChassisControllerBuilder()
					   .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {-PORT_RIGHT_BACK, -PORT_RIGHT_FRONT})
					   .withDimensions(AbstractMotor::gearset::blue, {{1.77_in, 10_in}, imev5BlueTPR})
					   .build();

auto profileController = AsyncMotionProfileControllerBuilder()
							 .withLimits({MAX_VEL, MAX_ACC, MAX_JERK})
							 .withOutput(chassisAuto)
							 .buildMotionProfileController();

auto turnProfileController = AsyncMotionProfileControllerBuilder()
								 .withLimits({MAX_VEL, MAX_ACC, MAX_JERK})
								 .withOutput(chassis)
								 .buildMotionProfileController();

void _chassisArcade()
{
	chassis->getModel()->arcade(master.getAnalog(ControllerAnalog::rightX), master.getAnalog(ControllerAnalog::leftY));
}

void _printChassisInfo()
{
}

void _chassisTask(void *parameter)
{
	while (true)
	{
		_chassisArcade();
		pros::delay(20);
	}
}

void chassisGenerateStraightPath(okapi::QLength inches, std::string pathName)
{
	profileController->generatePath({{0_in, 0_in, 0_deg}, {inches, 0_in, 0_deg}}, pathName);
}

void chassisGeneratePath(okapi::QLength x, okapi::QLength y, okapi::QAngle degrees, std::string pathName, bool async, bool mirrored)
{

	profileController->generatePath({{0_in, 0_in, 0_deg}, {x, y, degrees}}, pathName);
}

void chassisGenerateSlowStraightPath(okapi::QLength inches, std::string pathName, bool async, double maxVel)
{
	profileController->generatePath({{0_in, 0_in, 0_deg}, {inches, 0_in, 0_deg}}, pathName, {maxVel, MAX_ACC, MAX_JERK});
}

void chassisExecutePath(std::string pathName, bool async, bool backwards)
{
	profileController->removePath(lastPath);
	lastPath = pathName;
	profileController->setTarget(pathName, backwards);
	if (!async)
	{
		profileController->waitUntilSettled();
	}
}

void chassisForward(okapi::QLength inches, std::string pathName, bool async)
{
	profileController->removePath(lastPath);
	profileController->generatePath({{0_in, 0_in, 0_deg}, {inches, 0_in, 0_deg}}, pathName);
	lastPath = pathName;
	profileController->setTarget(pathName);
	if (!async)
	{
		profileController->waitUntilSettled();
	}
}

void chassisForwardSlow(okapi::QLength inches, std::string pathName, bool async, double maxVel)
{
	profileController->removePath(lastPath);
	profileController->generatePath({{0_in, 0_in, 0_deg}, {inches, 0_in, 0_deg}}, pathName, {maxVel, MAX_ACC, MAX_JERK});
	lastPath = pathName;
	profileController->setTarget(pathName);
	if (!async)
	{
		profileController->waitUntilSettled();
	}
}

void chassisBackward(okapi::QLength inches, std::string pathName, bool async)
{
	profileController->removePath(lastPath);
	profileController->generatePath({{0_in, 0_in, 0_deg}, {inches, 0_in, 0_deg}}, pathName);
	lastPath = pathName;
	profileController->setTarget(pathName, true);
	if (!async)
	{
		profileController->waitUntilSettled();
	}
}

void chassisBackwardSlow(okapi::QLength inches, std::string pathName, bool async, double maxVel)
{
	profileController->removePath(lastPath);
	profileController->generatePath({{0_in, 0_in, 0_deg}, {inches, 0_in, 0_deg}}, pathName, {maxVel, MAX_ACC, MAX_JERK});
	lastPath = pathName;
	profileController->setTarget(pathName, true);
	if (!async)
	{
		profileController->waitUntilSettled();
	}
}

void chassisTurn(okapi::QLength degrees, std::string pathName, bool async, bool right)
{
	// okapi::QLength inches = PI * 10 / (360 * static_cast<double> * inch);
	turnProfileController->removePath(lastTurnPath);
	turnProfileController->generatePath({{0_in, 0_in, 0_deg}, {2 * degrees, 0_in, 0_deg}}, pathName);
	lastTurnPath = pathName;
	turnProfileController->setTarget(pathName, right);
	if (!async)
	{
		turnProfileController->waitUntilSettled();
	}
}

void chassisWaitUntilSettled()
{
	profileController->waitUntilSettled();
}

void chassisMove(okapi::QLength x, okapi::QLength y, okapi::QAngle degrees, std::string pathName, bool async, bool mirrored)
{
	profileController->removePath(lastPath);
	profileController->generatePath({{0_in, 0_in, 0_deg}, {x, y, degrees}}, pathName);
	lastPath = pathName;
	profileController->setTarget(pathName, true);
	if (!async)
	{
		profileController->waitUntilSettled();
	}
}

void chassisInit()
{
	std::string text("Chassis");
	pros::Task my_task(_chassisTask, &text, "");
}