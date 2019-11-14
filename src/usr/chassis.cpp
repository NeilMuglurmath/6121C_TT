#include "main.h"

Controller master;

auto chassis = ChassisControllerFactory::create({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {PORT_RIGHT_BACK, PORT_RIGHT_FRONT}, AbstractMotor::gearset::blue);

void _chassisArcade()
{
	chassis.arcade(master.getAnalog(ControllerAnalog::rightX), master.getAnalog(ControllerAnalog::leftY));
}

void _chassisTask(void *parameter)
{
	while (true)
	{
		// if (!pros::competition::is_autonomous)
		// {
		_chassisArcade();
		// }
		pros::delay(20);
	}
}

void chassisInit()
{
	std::string text("Chassis");
	pros::Task my_task(_chassisTask, &text, "");
}

void chassisJankAutoJawn()
{
	chassis.left(-.25);
	chassis.right(.25);
	pros::delay(1300);
	chassis.stop();
}