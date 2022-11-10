#include "main.h"
#include "global.h"
#include "driver.h"
#include "auton.h"
#include "pid.h"
#include "lib/auton_obj.h"

using namespace glb;
using namespace pros;


void initialize() 
{
	lcd::initialize();
	con.clear();
	static Auton temp = auton_selector(autons);
	auton = &temp;

	// tasks
	Task fw_ctrl(pid::fw_pid);
}

void autonomous()
{
	(*auton).run();
	pid::recover = true;
}

void opcontrol() 
{
	int time = 0;

	while(true)
	{
		arcade_drive();
		flywheel_control();
		intake_control();
		print_info(time);

		if(con.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			autonomous();
		if(con.get_digital(E_CONTROLLER_DIGITAL_LEFT))
			calibrate_robot();
		
		delay(10);
		time += 10;
	}
}