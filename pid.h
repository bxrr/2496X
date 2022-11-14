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
    // chassis movement
    double global_heading = 0;

    void drive(double distance, int timeout=5000)
    {
        int time = 0;

        // constants
        double kP = 0.14;
        double kI = 0.32;
        double kD = 0;

        double straight_kI = 1.5;

        // initialize drive pid variables
        double start_pos = glb::chas.pos();
        double error = distance - (glb::chas.pos() - start_pos);
        double last_error;
        double integral = 0;

        // initialize straight pid variables
        glb::imu.set_heading(180);
        double init_heading = glb::imu.get_heading();
        double straight_i = 0;

        // variables for exiting if within 5 error for 100ms
        bool within_err = false;
        int within_err_time = 0;

        double slew = 0.05;

        while(time < timeout)
        {
            // calculate drive pid variables
            last_error = error;
            error = distance - (glb::chas.pos() - start_pos);

            if(abs(error)<100) integral += error / 100;

            double derivative = (error - last_error) * 100;

            // check for exit condition
            if(abs(error) < 7)
            {
                if(within_err == false)
                {
                    within_err = true;
                    within_err_time = time;
                }
                else
                {
                    if(within_err_time + 100 <= time)
                        break;
                }
            }
            else
            {
                within_err = false;
            }

            // calculate correction pid variables and speed
            double speed = error * kP + integral * kI + derivative * kD;
            if(abs(speed) > 127) speed = speed / abs(speed) * 127;

            straight_i += (glb::imu.get_heading() - init_heading) / 100;
            double correction = straight_i * straight_kI;

            slew += slew <= 1 ? 0.05 : 0;
            slew = slew > 1 ? 1 : slew;

            // apply speed
            glb::chas.spin_left(slew * (speed - correction));
            glb::chas.spin_right(slew * (speed + correction));

            // print stuff
            if(time % 50 == 0)
                glb::con.print(0, 0, "err: %.2lf c: %.2lf        ", init_heading-glb::imu.get_heading(), correction);

            // update time
            pros::delay(10);
            time += 10;
        }

        // stop chassis at end of loop
        glb::chas.stop();
        global_heading += glb::imu.get_heading() - init_heading;
    }

    void drive_const(double distance, int speed=127, int timeout=5000)
    {
        int time = 0;
        double start_pos = glb::chas.pos();
        double target = start_pos + distance;
        double s = distance / fabs(distance) * abs(speed);
        
        double straight_kI = 1.5;
        double straight_i = 0;
        glb::imu.set_heading(180);
        double init_heading = glb::imu.get_heading();

        while((distance < 0 ? glb::chas.pos() > target : glb::chas.pos() < target) && time < timeout)
        {
            straight_i += (glb::imu.get_heading() - init_heading) / 100;
            double correction = straight_i * straight_kI;
            glb::chas.spin_left(s - correction);
            glb::chas.spin_right(s + correction);
            pros::delay(10);
            time += 10;
        }

        glb::chas.stop();
        global_heading += glb::imu.get_heading() - init_heading;
    }

    void turn(double degrees, int timeout=3000)
    {
        int time = 0;

        // constants
        double kP = 0.9;
        double kI = 20.0;
        double kD = 0;

        auto f_k = [](double error) { return error / abs(error) * 30 * log(0.25 * (abs(error) + 4)) + 5; };

        // initialize pid variables
        glb::imu.set_heading(degrees > 0 ? 30 : 330);
        double start_pos = glb::imu.get_heading();
        double error = degrees - (glb::imu.get_heading() - start_pos);
        double last_error;
        double integral = 0;

        // variables for exiting if within 0.1 error for 100ms
        bool within_err = false;
        int within_err_time = 0;

        while(time < timeout)
        {
            // calculate pid 
            last_error = error;
            error = degrees - (glb::imu.get_heading() - start_pos);
            if(abs(error) < 8) integral += error / 100;
            double derivative = (error - last_error) * 100;

            // check for exit condition
            if(abs(error) <= 0.1)
            {
                if(within_err == false)
                {
                    within_err = true;
                    within_err_time = time;
                }
                else
                {
                    if(within_err_time + 100 <= time)
                        break;
                }
            }
            else
            {
                within_err = false;
            }

            // calculate speed
            double speed = kP * f_k(error) + integral * kI + derivative * kD;
            if(abs(speed) > 127) speed = speed / abs(speed) * 127;

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
        glb::chas.stop();
        global_heading += glb::imu.get_heading() - start_pos;
    }

    void turn_to(double degree_to, int timeout=3000)
    {
        double degree = degree_to - global_heading;
        degree = (degree > 180) ? -(360 - degree) : ((degree < -180) ? (360 + degree) : (degree)); // optimize the turn direction
        turn(degree, timeout);
    }

    void arc_turn(double degrees, double radius_enc, int timeout=5000, bool left_outer=true)
    {
        // define wheelbase information (set manually before usage of function)
        double wheelbase_in = 12.5; // in inches
        auto enc_conv = [](double in) { return (500 * in) / (2 * M_PI * 3.25); };
        double wheelbase_enc = enc_conv(wheelbase_in);

        // reset imu
        glb::imu.set_heading(degrees > 0 ? 30 : 330);
        double init_heading = glb::imu.get_heading();

        // initial variablespros m
        double right_start = glb::chas.right_pos();
        double left_start = glb::chas.left_pos();

        // define inner and outer targets
        double inner_target = 2 * M_PI * radius_enc * degrees / 360 + right_start;
        double outer_target = 2 * M_PI * (radius_enc + wheelbase_enc) * degrees / 360 + left_start;

        // inner radius PID variables
        double inner_error = inner_target - glb::chas.right_pos();
        double inner_i = 0;
        double last_inner_err;

        // outer radius PID variables
        double outer_error = outer_target - glb::chas.left_pos();
        double outer_i = 0;
        double last_outer_err;

        // outer radius difference from ideal location based on inner distance PID variables
        double rem_inner_deg = degrees * (inner_error / inner_target);
        double ideal_outer_err = (rem_inner_deg / degrees) * outer_target;
        double outer_diff_err = ideal_outer_err - outer_error;
        double outer_diff_i = 0;
        double last_outer_diff;

        // degree difference from ideal degree based on current inner distance using imu PID variables
        double ideal_deg = degrees * ((inner_target - inner_error) / inner_target);
        double deg_err = ideal_deg - (init_heading - glb::imu.get_heading());
        double deg_i = 0;
        double last_deg_err;

        // define constants and time;
        double kP = 0.1;
        double kI = 0.0;
        double kD = 0;

        double diff_kP = 0.00;
        double diff_kI = 0;
        double diff_kD = 0;

        double imu_kP = 0.5;
        double imu_kI = 0;
        double imu_kD = 0;

        int time = 0;

        while(time < timeout)
        {
            // update inner radius variables
            last_inner_err = inner_error;
            inner_error = inner_target - glb::chas.right_pos();
            inner_i += inner_error / 100;
            double inner_d = (inner_error - last_inner_err) * 100;

            // update outer radius variables
            last_outer_err = outer_error;
            outer_error = outer_target - glb::chas.left_pos();
            outer_i += outer_error / 100;
            double outer_d = (outer_error - last_outer_err) * 100;

            // update ideal difference variables
            rem_inner_deg = degrees * (inner_error / inner_target);
            ideal_outer_err = (rem_inner_deg / degrees) * outer_target;
            last_outer_diff = outer_diff_err;
            outer_diff_err = ideal_outer_err - outer_error; // outer_diff_err > 0 means outer side is going too fast. outer_diff_err < 0 means outer side is going too slow
            outer_diff_i += outer_diff_err / 100;
            double outer_diff_d = (outer_diff_err - last_outer_diff) * 100;

            // update degree difference variables
            ideal_deg = degrees * ((inner_target - inner_error) / inner_target);
            last_deg_err = deg_err;
            deg_err = ideal_deg - (init_heading - glb::imu.get_heading()); // deg_err > 0 means not turning fast enough. deg_err < 0 means turning too fast
            deg_i += deg_err / 100;
            double deg_d = (deg_err - last_deg_err) * 100;

            // check for exit condition
            // if(abs(inner_error) < 5 && abs(glb::chas.left_speed()) < 10)
            // {
            //     break;
            // }

            // calculate speeds
            auto f_ms = [](double speed) { return abs(speed) > 127 ? abs(speed) / speed * 127 : speed; }; // lambda function checking that speed does not exceed 127
            double rspeed = kP * inner_error + inner_i * kI + inner_d * kD; rspeed = f_ms(rspeed);
            double lspeed = kP * outer_error + outer_i * kI + outer_d * kD; lspeed = f_ms(rspeed);
            double dist_correction = diff_kP * outer_diff_err + diff_kI * outer_diff_i + outer_diff_d * diff_kD;
            double imu_correction = imu_kP * deg_err + imu_kI * deg_i + imu_kD * deg_d;

            // apply speed
            glb::chas.spin_left(lspeed - dist_correction + imu_correction);
            glb::chas.spin_right(rspeed + dist_correction - imu_correction);

            // update time
            pros::delay(10);
            time += 10;
        }

        // stop chassis at end of loop
        glb::chas.stop();
        global_heading += glb::imu.get_heading() - init_heading;
    }

    // flywheel ============================================================
    namespace fw
    {
        double flywheel_target = 0;
        bool recover = true;

        int time = 0;

        // constants
        double kP = 1.0;
        double kI = 0.1;
        double kD = 0.0;
        double kF = 0.2116666667;

        // initialize pid variables
        double actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;
        double error = 0; 
        double integral = 0;
        double last_error;
        double derivative = 0;
        double base_speed = 0;

        void fw_pid()
        {
            // count for average speed over n iterations
            auto f_window = [](double x, int w_s) { return pow(x+1 / w_s, 5); };

            double window[25];
            memset(window, 0, sizeof(window)); // 0 initialize window;
            int win_size = sizeof(window) / sizeof(window[0]);
            double win_avg = 0;

            // recovery delay
            int recover_start_time = 0;
            bool recover_start = false;

            while(true) // defined as a task; always running
            {
                double speed = flywheel_target;

                // calculate average speed
                actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;

                // calculate average of last n window of values weighted by an exponential function defined as f_window above
                memmove(window, window+1, sizeof(window[0]) * win_size-1);
                window[win_size-1] = actual_avg;
                
                double window_sum = 0;
                int n_terms = 0;
                for(int i = 0; i < win_size; i++)
                {
                    n_terms += f_window(i, win_size);
                    window_sum += window[i] * f_window(i, win_size);
                }
                win_avg = window_sum / n_terms;

                // flywheel recovery adds 150 to target speed
                if(glb::intakeR.get_actual_velocity() > 100 && speed != 0 && recover)
                {
                    if(recover_start == false)
                    {
                        recover_start = true;
                        recover_start_time = time;
                    }
                    else if(recover_start_time + 100 <= time)
                    {
                        speed += 150;
                    }
                }
                else
                {
                    recover_start = false;
                }
                
                // calculate pid variables
                double volt_speed = 0;
                last_error = error;
                error = speed - win_avg;
                integral += error / 100;
                derivative = (error - last_error) * 100;

                volt_speed = speed * kF + error * kP + integral * kI + derivative * kD;

                // apply speeds
                if(volt_speed < 0) volt_speed = 0; 

                // if target speed is set to 0, reset all variables
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

                // print rpm to controller
                if(speed != 0) printf("[%lf, %lf], ", win_avg, glb::intakeR.get_actual_velocity());

                // print stuff
                if(time % 100 == 0 && time % 1600 != 0)
                    glb::con.print(0, 0, "rpm: %.2lf", (win_avg));
                
                // update time
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
        return fw::actual_avg;
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