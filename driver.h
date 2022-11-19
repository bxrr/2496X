#ifndef __DRIVER__
#define __DRIVER__

#include "main.h"
#include "global.h"
#include "lib/auton_obj.h"
#include "pid.h"
#include <vector>

using namespace glb;
using namespace pros;

void arcade_drive()
{
    double left = abs(con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 10 ? con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) : 0;
    double right = abs(con.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) > 10 ? con.get_analog(E_CONTROLLER_ANALOG_RIGHT_X) : 0;

    if(left || right)
    {
        chas.spin_left(left + right);
        chas.spin_right(left - right);
    }
    else
    {
        chas.stop();
    }
}


void tank_drive()
{
    double left = abs(con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 10 ? con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) : 0;
    double right = abs(con.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) > 10 ? con.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) : 0;

    if(left || right)
    {
        chas.spin_left(left);
        chas.spin_right(right);
    }
    else
    {
        chas.stop();
    }
}

int flywheel_control()
{
    static int speed_index = 0;
    static bool fly_on = false;
    std::vector<int> speeds = {356, 390};
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        fly_on = !fly_on;

    if(fly_on)
    {
        if(angleP.get_status() == true)
            speed_index = 1;
        else
            speed_index = 0;

        pid::fw_spin(speeds[speed_index]);
    }
    else
    {
        pid::fw_stop();
    }

    return speed_index;
}

void intake_control()
{
    if(con.get_digital(E_CONTROLLER_DIGITAL_L2))
    {
        intakeL.move(127);
        intakeR.move(127);
    }
    else if(con.get_digital(E_CONTROLLER_DIGITAL_L1))
    {
        intakeL.move(-127);
        intakeR.move(-127);
    }
    else
    {
        intakeL.move(0);
        intakeR.move(0);
    }
    
    if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
    {
        intakeP.toggle();
    }
}

void angle_control()
{
    if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
        angleP.toggle();
}

int change_speed()
{
    static int num = 0;
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) && num < 2) num++;
    else if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) && num > 0) num--;
    return num;
}

void print_info(int time)
{

    if(time % 50 == 0 && time % 500 != 0 && time % 150 != 0 && time % 1600 != 0 && (pid::fw::actual_avg) <= 200)
        con.print(0, 0, "Chas Temp: %.1lf         ", chas.temp());
    if(time % 500 == 0 && time % 150 != 0 && time % 1600 != 0) 
        con.print(1, 0, "imu: %.2f            ", imu.get_heading());
    if(time % 150 == 0 && time % 1600 != 0)
        con.print(2, 0, "auton: %s         ", (*auton).get_name());
}

void calibrate_robot()
{
    imu.reset();
    chas.reset();
}

Auton auton_selector(std::vector<Auton> autons)
{
    short int selected = 0;
    int timer = 0;

    while(true)
    {
        if(!glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_A))
        {
            if(timer % 50 == 0 && timer % 100 != 0) 
                glb::con.print(0, 0, "Select: %s         ", autons.at(selected).get_name());

            if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) && selected > 0)
                selected--;

            if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && selected < autons.size()-1)
                selected++;
        }
        else
        {
            pros::delay(50);
            glb::con.clear();
            pros::delay(50);
            glb::con.print(0, 0, "Selected:         "); 
            pros::delay(50);
            glb::con.print(1, 0, "Auton: %s         ", autons.at(selected).get_name());   
            pros::delay(1500);
            glb::con.clear();
            return autons.at(selected);
        }

        pros::delay(1);
        timer++;
    }
}

#endif 
