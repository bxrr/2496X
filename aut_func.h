#ifndef __AUT_FUNC__
#define __AUT_FUNC__

#include "main.h"
#include "global.h"
#include "pid.h"
#include "driver.h"
#include "lib/chassis.h"


namespace auf
{
    void intake_vel(double speed=127)
    {
        glb::intakeL.move(-speed);
        glb::intakeR.move(-speed);
    }

    void intake_dist(double distance, double speed=600)
    {
        glb::intakeL.move(0);
        glb::intakeR.move(0);
        glb::intakeL.move_relative(-distance, speed);
        glb::intakeR.move_relative(-distance, speed);
    }

    void intake_stop()
    {
        glb::intakeL.brake();
        glb::intakeR.brake();
    }

    void index(int num_discs, int delay_ms=-1, int timeout=-1, bool recover=true)
    {
        if(delay_ms < 0) delay_ms = pid::fw_target();
        if(timeout < 0) timeout = num_discs * (delay_ms + 1000);

        int time = 0;
        int discs_shot = 0;
        int t_since_shot = 0;

        while(time < timeout && discs_shot < num_discs)
        {
            if(t_since_shot >= delay_ms)
            {
                if(abs(pid::fw_target() - pid::fw_speed()) < 2)
                {
                    t_since_shot = 0;
                    intake_dist(-410, -600);
                    discs_shot++;
                }
            }

            pros::delay(10);
            t_since_shot += 10;
            time += 10;
        }

        if(discs_shot < num_discs)
        {
            intake_dist(-2400);
        }

        pros::delay(500);
    }

    void shoot(int num_discs=3)
    {
        delay(300);
        intake_vel(70);
        delay(num_discs * 250);
        intake_vel(0);
    }

    void roller()
    {
        pid::drive_const(320, 70, 300);
        imu.set_heading(180);
        intake_dist(400);
        delay(600);
        pid::global_heading += imu.get_heading() - 180;
    }
}


#endif