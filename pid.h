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
    bool recover = false;

    double d_k(double error, double max_speed=127)
    {
        double offset = 200;
        return abs(error) / error * (error < offset) ? max_speed * sin(M_PI  * abs(error) / (2 * offset)) : max_speed;
    }

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
            integral += error / 100;
            double derivative = 100 * (error - last_error);

            // if(abs(error) < 15 && abs(glb::chas.speed()) < 15)
            // {
            //     break;
            // }

            double speed = d_k(error) * kP + integral * kI + derivative * kD;
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
            pros::delay(10);
            time += 10;
        }

        // stop chassis at end of loop
        glb::chas.stop();
        global_heading += init_heading - glb::imu.get_heading();
    }

    void turn(double degrees, int timeout=5000)
    {
        int time = 0;

        // constants
        double kP = 1.0;
        double kI = 0;
        double kD = 0;

        // initialize pid variables
        glb::imu.set_heading(180);
        double start_pos = glb::imu.get_heading();
        double error = degrees - (glb::imu.get_heading() - start_pos);
        double last_error;
        double integral = 0;

        auto f_k = [](double x) { return (127 * pow(x / 180, 0.6)); };

        while(time < timeout)
        {
            // calculate pid variables
            last_error = error;
            error = degrees - (glb::imu.get_heading() - start_pos);
            integral += error / 1000;
            double derivative = error - last_error;

            // if(abs(error) < 0.2 && abs(glb::chas_left.speed()) < 15)
            // {
            //     break;
            // }

            double speed = kP * f_k(error) + integral * kI + derivative * kD;
            if(abs(speed) > 127) speed = speed / abs(speed) * 127;

            // apply speed
            glb::chas.spin_left(speed);
            glb::chas.spin_right(-speed);

            // print stuff
            if(time % 60 == 0)
                glb::con.print(0, 0, "err: %.2lf         ", error);

            // update time
            pros::delay(10);
            time += 10;
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
        double kP = 0.5;
        double kI = 0.3;
        double kD = 0;

        // initialize pid variables
        double actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;
        double error = 0; 
        double integral = 0;
        double last_error;
        double base_speed = 0;
        double derivative;

        // count for average speed over n iterations
        auto f_w = [](double x, int w_s) { return pow(x+1 / w_s, 2); };

        double window[50];
        memset(window, 0, sizeof(window)); // 0 initialize window;
        int win_size = sizeof(window) / sizeof(window[0]);
        int cur_index = 0;

        while(true)
        {
            double speed = flywheel_target;

            // calculate average speed
            actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;

            // window layer 1
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
            cur_index++;
            double win_avg = window_sum / n_terms;

            // calculate pid variables
            double volt_speed = 0;
            if(glb::intakeL.get_actual_velocity() < -10 && glb::intakeR.get_actual_velocity() < -10 && speed != 0 && recover)
                speed += 65;

            last_error = error;
            error = speed - win_avg;
            integral += error / 100;
            derivative = 100 * (error - last_error);
            volt_speed = base_speed + error * kP + integral * kI + derivative * kD;

            // apply speeds
            if(volt_speed < 0) volt_speed = 0; 
            if(speed == 0)
            {
                volt_speed = 0;
                memset(window, 0, sizeof(window));
                error = 0;
                last_error = 0;
                integral = 0;
                derivative = 0;
            }
            glb::flywheelL = volt_speed;
            glb::flywheelR = volt_speed;
            printf("[%lf, %lf], ", win_avg, integral);

            // print stuff
            if(time % 60 == 0)
                glb::con.print(0, 0, "rpm: %.2lf", (win_avg));
            
            // update time
            pros::delay(10);
            time += 10;
        }
    }
}

#endif