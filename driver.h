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
    int flat_speeds[] = {310, 330, 350};
    int angle_speeds[] = {350, 370, 390};

    // set speed index
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        if(speed_index > 0) speed_index--;
    }
    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        if(speed_index < 2) speed_index++;
    }

    if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    {
        manual = !manual;
    }


    if(glb::con.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
        pid::fw_spin(-127);
    }
    else
    {
    // if not manual control, run distance sensor
        if(glb::con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        {
            fly_on = !fly_on;
        }

        if(fly_on)
        {
            if(manual)
            {
                if(glb::angleP.get_status()) pid::fw_spin(angle_speeds[speed_index]);
                else pid::fw_spin(flat_speeds[speed_index]);
            }
            else
            {
                if(glb::disc_sensor.get() < 65)
                {
                    intaken = false;
                    stopped = false;
                    if(unseen)
                    {
                        first_seen = time;
                        unseen = false;
                    }
                    last_disc = time;
                    if(first_seen + 200 < time)
                    {
                        if(glb::angleP.get_status()) pid::fw_spin(angle_speeds[speed_index]);
                        else pid::fw_spin(flat_speeds[speed_index]);
                    }
                }
                else if(last_disc + 250 <= time)
                {
                    unseen = true;
                    if(glb::intakeL.get_actual_velocity() < -100 || intaken)
                    {
                        intaken = true;
                        if(pid::fw::win_avg <= 0) 
                        {
                            stopped = true;
                            pid::fw_stop();
                        }
                        else if(!stopped)
                        {
                            pid::fw_spin(-75);
                        }
                    }
                    else
                    {
                        pid::fw_stop();
                    }
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
    double shoot_speed = glb::angleP.get_status() ? 127 : 100;
    //timothy tan

    pid::fw_recover(true);
    if(intake)
    {
        if(shoot)
        {
            intakeP.set(true);
            intakeL.move(shoot_speed);
            intakeR.move(shoot_speed);
        }
        else
        {
            intakeP.set(false);
            intakeL.move(-127);
            intakeR.move(-127);
        }
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
    
    if(con.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
        intakeP.set(true);
    }
    else if(!intake && !shoot)
    {
        intakeP.set(false);
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
