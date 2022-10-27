#ifndef __PID__
#define __PID__

#include "main.h"
#include "global.h"
#include <vector>
#include <numeric>
#include <stdio.h>
#include <cmath>


namespace pid
{
    double global_heading = 0;

    // flywheel
    double flywheel_target = 0;
    bool flywheel_recover = false;
    int flywheel_recover_start = 0;

    void drive(double distance, int timeout=5000)
    {
        int time = 0;

        // constants
        double kP = 1.0;
        double kI = 0;
        double kD = 0;

        double straight_kI = 0;

        // initialize drive pid variables
        double start_pos = glb::chas.pos();
        double error = distance - (glb::chas.pos() - start_pos);
        double last_error;
        double integral = 0;

        // initialize straight pid variables
        double init_heading = glb::imu.get_heading(); 
        double straight_i = 0;

        while(time < timeout)
        {
            // calculate drive pid variables
            last_error = error;
            error = distance - (glb::chas.pos() - start_pos);
            integral += error / 1000;
            double derivative = error - last_error;

            double speed = error * kP + integral * kI + derivative * kD;
            if(abs(speed) > 127) speed = speed / abs(speed) * 127;

            // calculate correction pid variables
            straight_i += (glb::imu.get_heading() - init_heading) / 1000;

            double correction = straight_i * straight_kI;

            // apply speed
            glb::chas.spin_left(speed - correction);
            glb::chas.spin_right(speed + correction);

            // print stuff
            if(time % 60 == 0)
                glb::con.print(0, 0, "err: %.2lf         ", error);

            // update time
            pros::delay(20);
            time += 20;
        }

        // stop chassis at end of loop
        glb::chas.stop();
        global_heading += init_heading - glb::imu.get_heading();
    }

    void turn(double degrees, int timeout=10000)
    {
        int time = 0;

        // constants
        double kP = 2.0;
        double kI = 0;
        double kD = 0;

        // initialize pid variables
        glb::imu.set_heading(180);
        double start_pos = glb::imu.get_heading();
        double error = degrees - (glb::imu.get_heading() - start_pos);
        double last_error;
        double integral = 0;

        while(time < timeout)
        {
            // calculate pid variables
            last_error = error;
            error = degrees - (glb::imu.get_heading() - start_pos);
            integral += error / 1000;
            double derivative = error - last_error;

            double speed = error * kP + integral * kI + derivative * kD;
            if(abs(speed) > 127) speed = speed / abs(speed) * 127;

            // apply speed
            glb::chas.spin_left(speed);
            glb::chas.spin_right(-speed);

            // print stuff
            if(time % 60 == 0)
                glb::con.print(0, 0, "err: %.2lf         ", error);

            // update time
            pros::delay(20);
            time += 20;
        }

        // stop chassis at end of loop
        glb::chas.stop();
        global_heading += start_pos - glb::imu.get_heading();
    }

    void turn_to(double degree_to, int timeout=5000)
    {
        double degree = degree_to - global_heading;
        degree = (degree > 180) ? -(360 - degree) : ((degree < -180) ? (360 + degree) : (degree)); // optimize the turn direction
        turn(degree, timeout);
    }

    void spin_flywheel()
    {
        int time = 0;

        // constants
        // double kP = 0.4; using exponential function for kP instead of constant
        auto f_kP = [](double x, double s) { return ((abs(x) / x) * s * pow(abs(x) / s, 1.7)); }; // = f_kP(x) = |x| / x * speed * (x/speed)^1.7
        double kI = 0.3;
        double kD = 0;

        // initialize pid variables
        double actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;
        double error = 0; 
        double integral = 0;
        double last_error;
        double base_speed = 0;

        // count for average speed over n iterations
        double window[20];
        int win_size = sizeof(window) / sizeof(window[0]);
        auto f_w = [](double x, int w_s) { return pow(x+1 / w_s, 2); };
        int cur_index = 0;

        while(true)
        {
            double speed = flywheel_target;

            // calculate average speed
            actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;
            if(cur_index >= win_size)
                    cur_index = 0;
            window[cur_index] = actual_avg;
            double window_sum = 0;
            int n_terms = 0;
            for(int i = 0; i < win_size; i++)
            {
                n_terms += f_w(i, win_size);
                window_sum += window[i] * f_w(i, win_size);
            }
            last_error = error;
            error = speed - window_sum / n_terms;
            cur_index++;

            // calculate pid variables
            integral += error / 100;
            double derivative = 100 * (error - last_error);

            // apply speeds
            double volt_speed = base_speed + f_kP(error, speed) + integral * kI + derivative * kD;
            if(volt_speed < 0 || speed == 0) volt_speed = 0; // check that voltage is not negative and target speed != 0
            else // check for steep drop in rpm and error is at least 5 below ideal for recovery
            {
                if(derivative > 100 && !flywheel_recover)
                {
                    flywheel_recover = true;
                    flywheel_recover_start = time;
                }
                if(flywheel_recover)
                {
                    if(time - flywheel_recover_start >= 1500)
                        flywheel_recover = false;
                    else   
                        volt_speed= 127;
                }
            }

            glb::flywheelL = volt_speed;
            glb::flywheelR = volt_speed;
            printf("[%lf, %lf], ", speed - error, f_kP(error, speed));

            // print stuff
            if(time % 60 == 0)
                glb::con.print(0, 0, "rpm: %.2lf", (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2);
            
            // update time
            pros::delay(10);
            time += 10;
        }
    }
}

#endif