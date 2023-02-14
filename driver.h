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
    double left = abs(con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 10 ? con.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) : 0;
    double right = abs(con.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) > 10 ? con.get_analog(E_CONTROLLER_ANALOG_RIGHT_X) : 0;

    auto turn_curve = [](double val) { return (val / abs(val) * 0.08873565094 * pow(abs(val), 1.5)); };
    if(right) right = turn_curve(right);

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

void flywheel_control(int time)
{
    static int speed_index = 0;
    static bool fly_on = false;
    static int last_disc = 0;
    static int first_seen = true;
    static bool unseen = true;
    static bool stopped = false;
    static bool manual = false;
    static bool intaken = false;
    int flat_speeds[] = {330, 360, 390, 420};
    int angle_speeds[] = {380, 410, 440, 470};

    // set speed index
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        if(speed_index > 0) speed_index--;
    }
    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        if(speed_index < 3) speed_index++;
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
            if(glb::disc_sensor.get() < 40)
            {
                intaken = false;
                stopped = false;
                if(unseen)
                {
                    first_seen = time;
                    unseen = false;
                }
                last_disc = time;
                if(first_seen + 300 < time)
                {
                    if(glb::angleP.get_status()) pid::fw_spin(angle_speeds[speed_index]);
                    else pid::fw_spin(flat_speeds[speed_index]);
                }
            }
            else if(last_disc + 400 <= time)
            {
                unseen = true;
                if(glb::intakeL.get_actual_velocity() < -40 || intaken)
                {
                    intaken = true;
                    if(pid::fw::win_avg <= 0) 
                    {
                        stopped = true;
                        pid::fw_stop();
                    }
                    else if(!stopped)
                    {
                        pid::fw_spin(-110);
                    }
                }
                else
                {
                    pid::fw_stop();
                }
            }
        }
        else
        {
            pid::fw_stop();
        }
    }
}

void intake_control()
{
    bool shoot = con.get_digital(E_CONTROLLER_DIGITAL_L2);
    bool intake = con.get_digital(E_CONTROLLER_DIGITAL_L1);
    double shoot_speed = glb::angleP.get_status() ? -2 * (pid::fw::flywheel_target - 380) + 127 : -0.8 * (pid::fw::flywheel_target - 340) + 55;
    if(shoot_speed < 35) shoot_speed = 35;

    pid::fw_recover(true);
    if(intake)
    {
        intakeL.move(-127);
        intakeR.move(-127);
    }
    else if(shoot)
    {
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
    static bool first_pressedA = false;
    static int first_pressed_timeA = 0;

    if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        if(first_pressedA)
        {
            expansionP.toggle();
        }
        first_pressedA = true;
        first_pressed_timeA = time;
    }

    if(first_pressed_timeA + 200 < time)
        first_pressedA = false;

    static bool first_pressedB = false;
    static int first_pressed_timeB = 0;

    if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    {
        if(first_pressedB)
        {
            sideExpandP.toggle();
        }
        first_pressedB = true;
        first_pressed_timeB = time;
    }

    if(first_pressed_timeB + 200 < time)
        first_pressedB = false;
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
