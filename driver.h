#ifndef __DRIVER__
#define __DRIVER__

#include "main.h"
#include "global.h"
#include "lib/auton_obj.h"
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

void spin_flywheel(double speed, int time)
{
    // constants
    double kP = 1.0;
    double kI = 1.0;
    double kD = 3.0;

    // initialize pid variables
    double actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;

    static bool reset = true;
    static double error = actual_avg - speed; 
    static double integral = 0;
    static double last_error = speed;
    static double last_time = time;

    if(reset)
    {
        error = actual_avg - speed;
        integral = 0;
        last_error = speed;
        last_time = time;
        reset = false;
    }

    if(speed == 0)
    {
        reset = true;
        glb::flywheelL = 0;
        glb::flywheelR = 0;
    }
    else
    {
        // calculate pid variables
        last_error = error;
        error = actual_avg - speed;
        integral += error * (time - last_time) / 1000;
        last_time = time;
        double derivative = error - last_error;

        double volt_speed = -error * kP - integral * kI + derivative * kD;

        // apply speeds
        glb::flywheelL = volt_speed;
        glb::flywheelR = volt_speed;
    }  
}

int change_speed()
{
    static int num = 0;
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) && num < 2) num++;
    else if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) && num > 0) num--;
    return num;
}

void flywheel_control(int speed_index, int time)
{
    int speeds[] = {380, 400, 440};
    static bool on = false;
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) on = !on;
    if(on)
        spin_flywheel(speeds[speed_index], time);
    else
        spin_flywheel(0, 0);
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
