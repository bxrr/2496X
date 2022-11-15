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
            if(abs(pid::fw_target() - pid::fw_speed()) < 2 && t_since_shot >= delay_ms)
            {
                t_since_shot = 0;
                intake_dist(-600);
                discs_shot++;
            }

            pros::delay(1);
            t_since_shot++;
            time++;
        }

        if(discs_shot < num_discs)
        {
            intake_dist(-1800);
        }
    }
}


#endif