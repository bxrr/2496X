#ifndef __AUT_FUNC__
#define __AUT_FUNC__

#include "main.h"
#include "global.h"

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
        if(delay_ms < 0) delay_ms = pid::flywheel_target * 5;
        if(timeout < 0) timeout = num_discs * (delay_ms + 1000);

        int time = 0;
        int discs_shot = 0;
        int t_since_shot = 0;
        while(time < timeout && discs_shot < num_discs)
        {
            if(abs(pid::flywheel_target - pid::actual_avg) < 5 && t_since_shot >= delay_ms)
            {
                intake_dist(-310);
                discs_shot++;
                t_since_shot = 0;
            }

            pros::delay(1);
            t_since_shot++;
            time++;
        }
    }
}


#endif