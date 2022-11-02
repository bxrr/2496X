#ifndef __DRIVER__
#define __DRIVER__

#include "main.h"
#include "global.h"
#include "lib/auton_obj.h"
#include "pid.h"
#include <string>
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

void flywheel_control()
{
    static int speed_index = 0;
    static bool fly_on = false;
    std::vector<int> speeds = {360, 500};
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
        fly_on = !fly_on;

    if(fly_on)
    {
        if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) && speed_index < speeds.size()) speed_index++;
        else if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) && speed_index > 0) speed_index--;
        pid::flywheel_target = speeds[speed_index];
    }
    else
    {
        pid::flywheel_target = 0;
    }
}

void intake_control()
{
    if(con.get_digital(E_CONTROLLER_DIGITAL_L1))
    {
        intakeL.move(127);
        intakeR.move(127);
    }
    else if(con.get_digital(E_CONTROLLER_DIGITAL_R1))
    {
        intakeL.move(-127);
        intakeR.move(-127);
    }
    else
    {
        intakeL.move(0);
        intakeR.move(0);
    }
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

    if(time % 50 == 0 && time % 100 != 0 && time % 150 != 0 && (flywheelL.get_actual_velocity() + flywheelR.get_actual_velocity())/2 <= 100)
        con.print(0, 0, "Chassis Temp: %.1lf         ", chas.temp());
    if(time % 100 == 0 && time % 150 != 0) 
        con.print(1, 0, "%.2f : %.2f", imu.get_heading(), chas.pos());
    if(time % 150 == 0)
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
