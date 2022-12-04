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

    if(abs(left) > 100) left = left/abs(left) * 2 * abs(left) - 100;
    if(abs(right) > 100) right = right/abs(right) * 2 * abs(right) - 100;

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

void flywheel_control(int time, bool run_driver=false)
{
    static int speed_index = 0;
    static bool manual_control = true;
    static bool fly_on = false;
    static bool driver_first = true;

    std::vector<int> speeds = {333, 385};

    static bool no_discs_first = true;
    static int no_discs_time = 0;

    // run driver
    if(run_driver && driver_first)
    {
        driver_first = false;
        manual_control = false;
    }

    // check manual control button
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    {
        pid::fw_stop();
        manual_control = !manual_control;
    }
    
    // set speed index
    if(angleP.get_status() == true)
        speed_index = 1;
    else
        speed_index = 0;

    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        pid::fw_spin(-127);
    }
    else
    {
    // if not manual control, run distance sensor
        if(!manual_control)
        {
            fly_on = false;
            if(pid::disc::two_discs)
            {
                pid::fw_spin(speeds[speed_index]);
            }
            else if(pid::disc::disc_present == false)
            {
                if(no_discs_first)
                {
                    no_discs_first = false;
                    no_discs_time = time;
                }
                else if(no_discs_time + 150 < time)
                {
                    pid::fw_stop();
                }
            }
            else
            {
                no_discs_first = true;
            }
        }
        else // if manual control, check for button press R1 to toggle flywheel
        {
            if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
            {
                fly_on = !fly_on;
            }

            if(fly_on)
            {
                pid::fw_spin(speeds[speed_index]);
            }
            else
            {
                pid::fw_stop();
            }
        }
    }
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

void expansion(int time)
{
    static bool first_pressed = false;
    static int first_pressed_time = 0;

    if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        if(first_pressed)
        {
            expansionP.toggle();
        }
        first_pressed = true;
        first_pressed_time = time;
    }

    if(first_pressed_time + 300 < time)
        first_pressed = false;
}

void print_info(int time, bool chassis_on)
{
    if(time % 50 == 0 && time % 500 != 0 && time % 150 != 0 && time % 1600 != 0)
    {
        if(chassis_on) con.print(0, 0, "temp: %.1lf         ", chas.temp());
        else con.print(0, 0, "CHAS OFF (right)     ");
    }
    if(time % 500 == 0 && time % 150 != 0 && time % 1600 != 0  && (pid::fw_speed()) <= 150) 
        con.print(1, 0, "imu: %.2f            ", glb::imu.get_heading());
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
