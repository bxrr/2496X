#ifndef __PID__
#define __PID__

#include "main.h"
#include "global.h"
#include <vector>
#include <numeric>
#include <stdio.h>
#include <cmath>
#include <cstring>


namespace pid
{
    double global_heading = 0;
    double last_heading = glb::imu.get_heading();

    void drive(double distance, int timeout=3000, double max_speed = 127)
    {
        int time = 0;

        // constants
        double kP = (abs(distance) < 200) ? 0.8 : 0.6;
        double kI = 3.0;
        double kD = 0.058;

        double straight_kI = 0.8;

        // initialize drive pid variables
        double start_pos = glb::chas.pos();
        double error = distance - (glb::chas.pos() - start_pos);
        double last_error;
        double integral = 0;

        // initialize straight pid variables
        double init_heading = global_heading;
        double cur_heading = glb::imu.get_heading();
        
        double straight_i = 0;

        // variables for exiting if within 5 error for 100ms
        bool within_err = false;
        int within_err_time = 0;

        double slew = 0.1;

        while(time < timeout)
        {
            // calculate drive pid variables
            last_error = error;
            error = distance - (glb::chas.pos() - start_pos);

            if(abs(error) < 50) integral += error / 100;

            double derivative = (error - last_error) * 100;

            // check for exit condition
            if(abs(error) < 10)
            {
                if(within_err == false)
                {
                    within_err = true;
                    within_err_time = time;
                }
                else
                {
                    if(within_err_time + 150 <= time)
                        break;
                }
            }
            else
            {
                within_err = false;
            }

            // calculate correction pid variables and speed
            double speed = error * kP + integral * kI + derivative * kD;
            if(abs(speed) > max_speed) speed = speed / abs(speed) * max_speed;

            // correction
            last_heading = cur_heading;
            cur_heading = glb::imu.get_heading();

            if(cur_heading - last_heading > 100)
            {
                global_heading += (cur_heading - 360) - last_heading;
            }
            else if(cur_heading - last_heading < -100)
            {
                global_heading += cur_heading + (360 - last_heading);
            }
            else
            {
                global_heading += cur_heading - last_heading;
            }

            straight_i += (global_heading - init_heading) / 100;
            double correction = abs(speed) / 75 * straight_i * straight_kI;

            slew += slew <= 1 ? 0.1 : 0;
            slew = slew > 1 ? 1 : slew;

            // apply speed
            glb::chas.spin_left(slew * (speed - correction));
            glb::chas.spin_right(slew * (speed + correction));

            // print stuff
            if(time % 50 == 0)
                glb::con.print(0, 0, "err: %.2lf c: %.2lf        ", error, within_err_time);

            // update time
            pros::delay(10);
            time += 10;
        }

        // stop chassis at end of loop
        printf("d: %lf - %d\n", error, time);
        glb::chas.stop();
    }

    void drive_const(double distance, int speed=127, int timeout=3000)
    {
        int time = 0;
        double start_pos = glb::chas.pos();
        double target = start_pos + distance;
        double s = distance / fabs(distance) * abs(speed);
        
        double straight_kI = 0.8;
        double straight_i = 0;
        double init_heading = global_heading;
        double cur_heading = glb::imu.get_heading();

        while((distance < 0 ? glb::chas.pos() > target : glb::chas.pos() < target) && time < timeout)
        {
            last_heading = cur_heading;
            cur_heading = glb::imu.get_heading();

            if(cur_heading - last_heading > 100)
            {
                global_heading += (cur_heading - 360) - last_heading;
            }
            else if(cur_heading - last_heading < -100)
            {
                global_heading += cur_heading + (360 - last_heading);
            }
            else
            {
                global_heading += cur_heading - last_heading;
            }

            straight_i += (global_heading - init_heading) / 100;
            double correction = straight_i * straight_kI;
            
            glb::chas.spin_left(s - correction);
            glb::chas.spin_right(s + correction);
            pros::delay(10);
            time += 10;
        }

        glb::chas.stop();
    }
    
    void turn(double degrees, int timeout=2000)
    {
        int time = 0;

        double kP, kI, kD;
        // constants
        
        double a = 4.92973;
        double b = 0.985783;
        double c = 5.61611;

        //Exponential Model; kP = ab^x + c

        kP = degrees >= 30 ? a*pow(b,degrees)+c : 10;
        kI = 8;
        kD = degrees >= 30 ? 0.44 : 0.31;

        // if(abs(degrees) > 120)
        // {
        //     kP = 6.0;
        //     kI = 8; //18
        //     kD = 0.44; //0.4
        // }
        // else if(abs(degrees) > 90) //70
        // {
        //     kP = 6.47;
        //     kI = 8; //18
        //     kD = 0.44; //.35
        // }
        // else if(abs(degrees) > 45) //testing
        // {
        //     kP = 7;
        //     kI = 8; //18
        //     kD = 0.44; //.35
        // }
        // else if(abs(degrees) > 20)
        // {
        //     kP = 8.2;
        //     kI = 8;
        //     kD = 0.44;
        // }
        // else
        // {
        //     kP = 10.0;
        //     kI = 18;
        //     kD = 0.4;
        // }

        // inertial wrapping
        double init_heading = global_heading;
        double cur_heading = glb::imu.get_heading();

        // initialize pid variables
        double error = degrees - global_heading;
        double last_error;
        double integral = 0;

        // variables for exiting if within 0.1 error for 250ms
        bool within_err = false;
        int within_err_time = 0;

        while(time < timeout)
        {
            // inertial wrapping
            last_heading = cur_heading;
            cur_heading = glb::imu.get_heading();

            if(cur_heading - last_heading > 100)
            {
                global_heading += (cur_heading - 360) - last_heading;
            }
            else if(cur_heading - last_heading < -100)
            {
                global_heading += cur_heading + (360 - last_heading);
            }
            else
            {
                global_heading += cur_heading - last_heading;
            }

            // calculate pid
            last_error = error;
            error = degrees - (global_heading - init_heading);
            double derivative = (error - last_error) * 100;
            if(abs(error) < 5) integral += error / 100;

            // check for exit condition
            if(abs(error) <= 0.15)
            {
                if(within_err == false)
                {
                    within_err = true;
                    within_err_time = time;
                }
                else
                {
                    if(within_err_time + 150 <= time)
                        break;
                }
            }
            else
            {
                within_err = false;
            }

            // calculate speed
            double speed = kP * error + integral * kI + derivative * kD;

            glb::chas.spin_left(speed);
            glb::chas.spin_right(-speed);

            // print stuff
            if(time % 50 == 0)
                glb::con.print(0, 0, "err: %.2lf         ", error);

            // update time
            pros::delay(10);
            time += 10;
        }

        // stop chassis at end of loop
        printf("t: %lf - %d - %lf\n", error, time, glb::imu.get_heading());
        glb::chas.stop();
    }

    void turn_to(double degree_to, int timeout=3500)
    {
        double degree = degree_to - global_heading;
        degree = (degree > 180) ? -(360 - degree) : ((degree < -180) ? (360 + degree) : (degree)); // optimize the turn direction
        turn(degree, timeout);
    }

    // flywheel =============================================================
    namespace fw
    {
        double flywheel_target = 0;
        bool recover = true;

        int time = 0;

        // constants
        double kP = 0.8;
        double kI = 0.8;
        double kD = 0.0;
        double kF = 0.191;
        double full_speed = 50;

        // initialize pid variables
        double actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;
        double error = 0; 
        double integral = 0;
        double last_error;
        double derivative = 0;
        double base_speed = 0;

        double win_avg = 0;

        void const_eq(double err)
        {
            if(flywheel_target < 440)
            {
                kP = 0.8;
                kI = 0.8;
                full_speed = 30;
            }
            else
            {
                kP = 2.0;
                kI = 0.3;
                full_speed = 10;
            }
        }

        void fw_pid()
        {
            // moving average vars
            double window[50];
            memset(window, 0, sizeof(window)); // 0 initialize window;
            int win_size = sizeof(window) / sizeof(window[0]);
            win_avg = 0;

            auto f_window = [](int i, int win_size) { return pow((double) (i+1)/win_size, 2);}; // moving average weighting

            // recovery delay
            int recover_start_time = 0;
            bool recover_start = false;

            bool had_two = false;

            while(true) // defined as a task; always running
            {
                double speed = flywheel_target;

                // calculate average speed
                actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;

                // calculate average of last n window of values weighted by an exponential function defined as f_window above
                memmove(window, window+1, sizeof(window[0]) * win_size - sizeof(window[0]));
                window[win_size-1] = actual_avg;
                
                double window_sum = 0;
                double n_terms = 0;
                for(int i = 0; i < win_size; i++)
                {
                    window_sum += window[i] * f_window(i, win_size);
                    n_terms += f_window(i, win_size);
                }
                win_avg = window_sum / n_terms;

                // if target speed is set to 0, reset all variables
                if(flywheel_target == 0 || speed == 0)
                {
                    glb::flywheelL.move(0);
                    glb::flywheelR.move(0);
                    memset(window, 0, sizeof(window));
                    error = 0;
                    last_error = 0;
                    integral = 0;
                    derivative = 0;
                }
                else if(flywheel_target < 0)
                {
                    glb::flywheelL = flywheel_target;
                    glb::flywheelR = flywheel_target;
                    memset(window, 0, sizeof(window));
                    error = 0;
                    last_error = 0;
                    integral = 0;
                    derivative = 0;
                }
                else
                {
                    // calculate pid variables (different calculations for auton and not autonomous)
                    double volt_speed = 0;
                    last_error = error;
                    error = speed - win_avg;
                    if(abs(error) < 20) integral += error / 100;
                    else integral = 0;
                    derivative = (error - last_error);

                    const_eq(error);

                    double temp_kP = error < -5 ? kP / 20 : kP;
                    
                    volt_speed = speed * kF + error * temp_kP + integral * kI + derivative * kD;

                    // flywheel recovery adds to target speed
                    if(recover)
                    {
                        if(glb::intakeR.get_actual_velocity() > 30 && flywheel_target < 420)
                        {
                            if(recover_start == false)
                            {
                                recover_start = true;
                                recover_start_time = time;
                            }
                            else if(recover_start_time + 45 <= time)
                            {
                                volt_speed = 127;
                            }
                        }
                        else
                        {
                            recover_start = false;
                        }
                    }

                    if(volt_speed > 127) volt_speed = 127;
                    if(error > full_speed) volt_speed = 127;
                    if(volt_speed < 0) volt_speed = 0;

                    glb::flywheelL.move(volt_speed);
                    glb::flywheelR.move(volt_speed);

                    // print stuff

                    if(time % 100 == 0 && time % 1600 != 0 && win_avg > 150)
                        glb::con.print(1, 0, "rpm: %.2lf", (win_avg));
                }
                
                // update time
                if(speed != 0) printf("[%lf, %lf], ", win_avg, actual_avg);
                pros::delay(10);
                time += 10;
            }
        }
    }

    void fw_spin(double speed)
    {
        fw::flywheel_target = speed;
    }

    void fw_recover(bool on=true)
    {
        fw::recover = on;
    }

    double fw_speed()
    {
        return fw::win_avg;
    }

    void fw_stop()
    {
        fw_spin(0);
    }

    double fw_target()
    {
        return fw::flywheel_target;
    }
}

#endif