#include "main.h"

Controller master;

const double MAX_VEL = 1.2;
const double MAX_ACC = 1;
const double MAX_JERK = 4;

const double DISTANCE_KP = 0;
const double DISTANCE_KI = 0;
const double DISTANCE_KD = 0;

const double TURN_KP = 0;
const double TURN_KI = 0;
const double TURN_KD = 0;

const double ANGLE_KP = 0;
const double ANGLE_KI = 0;
const double ANGLE_KD = 0;

QLength lastX = 0_in;
QLength lastY = 0_in;
QAngle lastTheta = 0_deg;

std::string lastPath("");

auto chassis = ChassisControllerBuilder()
				   .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {PORT_RIGHT_BACK, PORT_RIGHT_FRONT})
				   .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10_in}, 128})
				   .build();

auto chassisAuto = ChassisControllerBuilder()
					   .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {-PORT_RIGHT_BACK, -PORT_RIGHT_FRONT})
					   .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10_in}, 128})
					   .build();

auto profileController = AsyncMotionProfileControllerBuilder()
							 .withLimits({MAX_VEL, MAX_ACC, MAX_JERK})
							 .withOutput(chassisAuto)
							 .buildMotionProfileController();

void _chassisArcade()
{
	chassis->getModel()->arcade(master.getAnalog(ControllerAnalog::rightX), master.getAnalog(ControllerAnalog::leftY));
}

void _chassisTask(void *parameter)
{
	while (true)
	{
		_chassisArcade();
		pros::delay(20);
	}
}

void chassisForward(okapi::QLength inches, std::string pathName)
{
	profileController->generatePath({{lastX, lastY, lastTheta}, {inches, lastY, lastTheta}}, pathName);
	lastPath = pathName;
	profileController->setTarget(pathName);
	profileController->waitUntilSettled();
}

void chassisInit()
{
	std::string text("Chassis");
	pros::Task my_task(_chassisTask, &text, "");
}