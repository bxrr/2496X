#ifndef __DRIVER__
#define __DRIVER__

#include "main.h"
#include "global.h"
#include "lib/auton_obj.h"
#include "pid.h"
#include <vector>
#include <cmath>

using namespace glb;
using namespace pros;

void arcade_drive()
{
    double left = abs(con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 20 ? con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) : 0;
    double right = abs(con.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) > 20 ? con.get_analog(E_CONTROLLER_ANALOG_RIGHT_X) : 0;

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
    double left = abs(con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 15 ? con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) : 0;
    double right = abs(con.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) > 15 ? con.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) : 0;

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

int flywheel_control(int time)
{
    static bool fly_on = false;
    int flat_speeds[] = {320, 330};
    int angle_speeds[] = {330, 350};
    static int speed_index = 0;

    // set speed index
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        if(speed_index > 0) speed_index--;
    }
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        if(speed_index < 1) speed_index++;
    }

    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        pid::fw_spin(-127);
    }
    else
    {   
        if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        {
            fly_on = !fly_on;
        }

        if(fly_on)
        {
    
            if(glb::angleP.get_status()) pid::fw_spin(angle_speeds[speed_index]);
            else pid::fw_spin(flat_speeds[speed_index]);
        }
        else
        {
            pid::fw_stop();
        }
    }

    return speed_index;
}

void intake_control(int speed_index)
{
    bool shoot = con.get_digital(E_CONTROLLER_DIGITAL_L2);
    bool intake = con.get_digital(E_CONTROLLER_DIGITAL_L1);
    double shoot_speed;
    if(angleP.get_status())
    {
        shoot_speed = speed_index == 0 ? 85 : 70;
    }
    else
    {
        shoot_speed = speed_index == 0 ? 85 : 70;
    }

    pid::fw_recover(true);
    if(intake)
    {
        // hoodP.set(true);
        intakeL.move(-127);
        intakeR.move(-127);
    }
    else if(shoot)
    {
        // hoodP.set(false);
        if(glb::disc_sensor1.get() > 40) shoot_speed = 127; 
        intakeL.move(shoot_speed);
        intakeR.move(shoot_speed);
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
    // yes
    static bool first_pressedA = false;
    static int first_pressed_timeA = 0;

    if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        if(first_pressedA)
        {
            expansionP.toggle();
        if ((*auton).get_name() == "skills")
        {
            glb::expansionP.set(true);
            for(int i = 0; i < 7; i++)
            {
                glb::expansionP.toggle();
                pros::delay(200);
            }
        }
        }
        first_pressedA = true;
        first_pressed_timeA = time;
    }

    if(first_pressed_timeA + 500 < time)
        first_pressedA = false;
}
void print_info(int time, bool chassis_on)
{
    if(time % 50 == 0 && time % 500 != 0 && time % 150 != 0 && time % 1600 != 0)
    {
        if(chassis_on) con.print(0, 0, "%.1lf:%.1lf:%.1lf         ", chas.temp(), (glb::flywheelL.get_temperature() + glb::flywheelR.get_temperature()) / 2, (glb::intakeL.get_temperature() + glb::intakeR.get_temperature()) / 2);
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
