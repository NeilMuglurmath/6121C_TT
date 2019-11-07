#include "main.h"

Controller master;

auto chassis = ChassisControllerFactory::create({PORT_LEFT_BACK, PORT_LEFT_FRONT}, {PORT_RIGHT_BACK, PORT_RIGHT_FRONT});

void chassisArcade()
{
	chassis.arcade(master.getAnalog(ControllerAnalog::rightX), master.getAnalog(ControllerAnalog::leftY));
}
