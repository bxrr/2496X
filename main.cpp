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
	imu.set_heading(0);
}

void autonomous()
{
	imu.set_heading(0);
	(*auton).run();
}

void opcontrol() 
{
	int time = 0;
	bool chassis_on = true;

	while(true)
	{
		pid::fw::force_recover = false;
		pid::fw_recover(true);
		if(chassis_on)
			arcade_drive();
			// tank_drive();
		else
			chas.stop();
		intake_control(flywheel_control(time));
		angle_control();
		//hood_control(time);
		expansion(time);
		print_info(time, chassis_on);

		if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT))
			chassis_on = !chassis_on;
		if(con.get_digital(E_CONTROLLER_DIGITAL_UP) && chassis_on)
			autonomous();
		
		delay(5);
		time += 5;
	}
}