#ifndef __PID__
#define __PID__

#include "main.h"
#include "global.h"


namespace pid
{
    double global_heading = 0;

    void drive(double distance, int timeout=5000)
    {
        int time = 0;

        // constants
        double kP = 1.0;
        double kI = 0;
        double kD = 0;

        double straight_kI = 0;

        // initialize drive pid variables
        double start_pos = glb::pos();
        double error = distance - (glb::pos() - start_pos);
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
            if(time % 50 == 0)
                con.print(0, 0, "err: %.2lf         ", error);

            // update time
            pros::delay(1);
            time++;
        }

        // stop chassis at end of loop
        chas.stop();
        global_heading += init_heading - glb::imu.get_heading();
    }

    void turn(double degrees, int timeout=5000)
    {
        int time = 0;

        // constants
        double kP = 2.0;
        double kI = 0;
        double kD = 0;

        // initialize pid variables
        glb::imu.set_heading(180);
        double start_pos = glb::imu.get_heading();
        double error = degrees - (glb::imu.get_heading() - start_pos());
        double last_error;
        double integral = 0;

        while(time < timeout)
        {
            // calculate pid variables
            last_error = error;
            error = degrees - (glb::imu.get_heading() - start_pos()
            integral += error / 1000;
            double derivative = error - last_error;

            double speed = error * kP + integral * kI + derivative * kD;
            if(abs(speed) > 127) speed = speed / abs(speed) * 127;

            // apply speed
            glb::chas.spin_left(speed);
            glb::chas.spin_right(-speed);

            // print stuff
            if(time % 50 == 0)
                con.print(0, 0, "err: %.2lf         ", error);

            // update time
            pros::delay(1);
            time++;
        }

        // stop chassis at end of loop
        chas.stop();
        global_heading += start_pos - glb::imu.get_heading();
    }

    void turn_to(double degree_to, int timeout=5000)
    {
        double degree = degree_to - global_heading;
        degree = (degree > 180) ? -(360 - degree) : ((degree < -180) ? (360 + degree) : (degree)); // optimize the turn direction
        turn(degree, timeout);
    }

    void flywheel(double speed, int timeout=5000)
    {
        double init_heading = glb::imu.get_heading();
        int time = 0;

        // constants
        double kP = 1.0;
        double kI = 1.0;
        double kD = 3.0;

        // initialize pid variables
        double actual_avg = (glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2;
        double error = actual_avg - speed; 
        double integral = 0;
        double last_error;

        // count for average speed over 10 iterations
        int count = 0;
        double temp_avg = 0;

        while(time < timeout)
        {
            // calculate average speed
            if(count < 10)
            {
                double temp_avg +=  0.1 * ((glb::flywheelL.get_actual_velocity() + glb::flywheelR.get_actual_velocity()) / 2);
                count++;
            }
            else
            {
                count = 0;
                temp_avg = 0;
                avg_speed = temp_avg;
            }

            // calculate pid variables
            last_error = error;
            error = speed - actual_avg;
            integral += error / 1000;
            double derivative = error - last_error;

            double volt_speed = error * kP + integral * kI + derivative * kD;
            if(volt_speed < 0) volt_speed = 0;

            // apply speeds
            glb::flywheelL = volt_speed;
            glb::flywheelR = volt_speed;

            // print stuff
            if(time % 50 == 0)
                con.print(0, 0, "rpm: %.2lf         ", actual_avg);

            // update time
            pros::delay(1);
            time++;
        }

        // stop flywheel after loop
        flywheelL = 0;
        flywheelR = 0;

        global_heading += init_heading - glb::imu.get_heading();
    }

    // double flywheel(double speed, void(*index)(), void(*stop_index)(), int timeout=5000)
    // {
    //     int time = 0;

    //     // constants
    //     double kP = 1.0;
    //     double kI = 0;
    //     double kD = 0;

    //     // initialize pid variables
    //     double actual_avg = (flywheelL.get_actual_velocity() + flywheelR.get_actual_velocity()) / 2;
    //     double error = speed - actual_avg; 
    //     double integral = 0;
    //     double last_error;

    //     // count for average speed over 10 iterations
    //     int count = 0;
    //     double temp_avg = 0;

    //     while(time < timeout)
    //     {
    //         // calculate average speed
    //         if(count < 10)
    //         {
    //             double temp_avg +=  0.1 * ((flywheelL.get_actual_velocity() + flywheelR.get_actual_velocity()) / 2);
    //             count++;
    //         }
    //         else
    //         {
    //             count = 0;
    //             temp_avg = 0;
    //             avg_speed = temp_avg;

    //             // index if within 5 of ideal rpm after avg_speed is updated
    //             if(abs(actual_avg - speed) <= 5) *index();
    //             else *stop_index();
    //         }

    //         // calculate pid variables
    //         last_error = error;
    //         error = speed - actual_avg;
    //         integral += error;

    //         double volt_speed = error * kP + integral * kI + derivative * kD;

    //         // apply speeds
    //         flywheelL = volt_speed;
    //         flywheelR = volt_speed;

    //         // print stuff
    //         if(time % 50 == 0)
    //             con.print(0, 0, "rpm: %.2lf         ", actual_avg);

    //         // update time
    //         pros::delay(1);
    //         time++;
    //     }

    //     // stop flywheel after loop
    //     flywheelL = 0;
    //     flywheelR = 0;
    // }
}

#endif