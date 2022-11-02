#ifndef __AUT_FUNC__
#define __AUT_FUNC__

#include "main.h"
#include "global.h"

namespace auf
{
    void intake_vel(double speed)
    {
        glb::intakeL = speed;
        glb::intakeR = speed;
    }

    void intake_dist(double distance, double speed=600)
    {
        glb::intakeL = 0;
        glb::intakeR = 0;
        glb::intakeL.move_relative(distance, speed);
        glb::intakeR.move_relative(distance, speed);
    }

    void intake_stop()
    {
        glb::intakeL.brake();
        glb::intakeR.brake();
    }
}


#endif