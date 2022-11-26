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
        glb::intakeL = -speed;
        glb::intakeR = -speed;
    }

    void intake_dist(double distance, double speed=600)
    {
        glb::intakeL = 0;
        glb::intakeR = 0;
        glb::intakeL.move_relative(-distance, speed);
        glb::intakeR.move_relative(-distance, speed);
    }

    void intake_stop()
    {
        glb::intakeL.brake();
        glb::intakeR.brake();
    }

    void index(int num_discs, int delay_ms=-1, int timeout=-1)
    {
        if(delay_ms < 0) delay_ms = pid::fw_target();
        if(timeout < 0) timeout = num_discs * (delay_ms + 1000);

        int time = 0;
        int discs_shot = 0;
        int t_since_shot = 0;
        while(time < timeout && discs_shot < num_discs)
        {
            if(abs(pid::fw_target() - pid::fw_speed()) < 1 && t_since_shot >= delay_ms)
            {
                t_since_shot = 0;
                intake_dist(-590);
                discs_shot++;
            }

            pros::delay(10);
            t_since_shot += 10;
            time += 10;
        }

        if(discs_shot < num_discs)
        {
            intake_dist(-2400);
        }

        pros::delay(300);
    }

    void shoot(int num_discs=3)
    {
        intake_vel(-127);
        delay(num_discs * 150);
        intake_vel(0);
    }

    void roller()
    {
        pid::drive_const(300, 70, 320);
        intake_dist(-600);
        delay(600);
    }
}


#endif