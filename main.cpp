#include "main.h"
#include "global.h"
#include "driver.h"
#include "auton.h"
#include "lib/auton_obj.h"

using namespace glb;
using namespace pros;


void initialize() 
{
	lcd::initialize();
	con.clear();
	static Auton temp = auton_selector(autons);
	auton = &temp;
}

void autonomous()
{
	(*auton).run();
}

void opcontrol() 
{
	int time = 0;

	while(true)
	{
		arcade_drive();
		flywheel_control(change_speed(), time);

		if(con.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			autonomous();
		if(con.get_digital(E_CONTROLLER_DIGITAL_LEFT))
			calibrate_robot();
		
		delay(1);
		time++;
	}
}