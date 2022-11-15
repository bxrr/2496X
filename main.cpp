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
	Task fw_ctrl(pid::fw::fw_pid);
}

void autonomous()
{
	(*auton).run();
}

void opcontrol() 
{
	int time = 0;
	bool chassis_on = true;

	while(true)
	{
		pid::fw_recover(true);
		if(chassis_on)
			arcade_drive();
		intake_control();
		angle_control();
		flywheel_control();
		print_info(time);

		if(con.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			autonomous();
		if(con.get_digital(E_CONTROLLER_DIGITAL_LEFT))
			calibrate_robot();
		if(con.get_digital(E_CONTROLLER_DIGITAL_RIGHT))
			chassis_on = !chassis_on;
		
		delay(10);
		time += 10;
	}
}