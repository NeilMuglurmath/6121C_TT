#include "main.h"

Controller master;

auto chassis = ChassisControllerBuilder()
    .withMotors({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {PORT_RIGHT_BACK, PORT_RIGHT_FRONT})
    // Green gearset, 4 in wheel diam, 11.5 in wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
    .build();

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

void chassisInit()
{
	std::string text("Chassis");
	pros::Task my_task(_chassisTask, &text, "");
}