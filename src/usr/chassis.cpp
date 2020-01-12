#include "main.h"

Controller master;

const double MAX_VEL = 1.2;
const double MAX_ACC = 1;
const double MAX_JERK = 4;

const double DISTANCE_KP = .0003;
const double DISTANCE_KI = 0.0005;
const double DISTANCE_KD = 0.000001;

const double TURN_KP = 0;
const double TURN_KI = 0;
const double TURN_KD = 0;

const double ANGLE_KP = 0;
const double ANGLE_KI = 0;
const double ANGLE_KD = 0;

auto chassis = ChassisControllerBuilder()
				   .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {PORT_RIGHT_BACK, PORT_RIGHT_FRONT})
				   .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10_in}, 700})
				   .withGains({DISTANCE_KP, DISTANCE_KI, DISTANCE_KD}, {TURN_KP, TURN_KI, TURN_KD}, {ANGLE_KP, ANGLE_KI, ANGLE_KD})
				   .withDerivativeFilters(
					   std::make_unique<AverageFilter<3>>(), // Distance controller filter
					   std::make_unique<AverageFilter<3>>(), // Turn controller filter
					   std::make_unique<AverageFilter<3>>()  // Angle controller filter
					   )
				   .build();

auto chassisAuto = ChassisControllerBuilder()
					   .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {-PORT_RIGHT_BACK, -PORT_RIGHT_FRONT})
					   .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10_in}, 700})
					   .withGains({DISTANCE_KP, DISTANCE_KI, DISTANCE_KD}, {TURN_KP, TURN_KI, TURN_KD}, {ANGLE_KP, ANGLE_KI, ANGLE_KD})
					   .withDerivativeFilters(
						   std::make_unique<AverageFilter<3>>(), // Distance controller filter
						   std::make_unique<AverageFilter<3>>(), // Turn controller filter
						   std::make_unique<AverageFilter<3>>()  // Angle controller filter
						   )
					   .build();

void _chassisArcade()
{
	chassis->getModel()->arcade(master.getAnalog(ControllerAnalog::rightX), master.getAnalog(ControllerAnalog::leftY));
}

void _printChassisInfo()
{
	c
}

void _chassisTask(void *parameter)
{
	while (true)
	{
		_chassisArcade();
		pros::delay(20);
	}
}

void chassisForward(okapi::QLength inches, bool async)
{
	if (async)
	{
		chassisAuto->moveDistanceAsync(inches);
	}
	else
	{
		chassisAuto->moveDistance(inches);
	}
}

void chassisBackward(okapi::QLength inches, bool async)
{
	if (async)
	{
		chassisAuto->moveDistanceAsync(-inches);
	}
	else
	{
		chassisAuto->moveDistance(-inches);
	}
}

void chassisInit()
{
	std::string text("Chassis");
	pros::Task my_task(_chassisTask, &text, "");
}