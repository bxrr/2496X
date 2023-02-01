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

     void open_intake() {
        intakeP.set(true);
        intake_vel();
    }
    void close_intake() {
        intakeP.set(false);
        intake_stop();
    }

    void index(int num_discs=3, int ms_delay=500)
    {
        for(int i = 0; i < num_discs; i++)
        {
            intake_vel(-127);
            delay(175);
            intake_vel(0);
            if(i < num_discs-1) pros::delay(ms_delay);
        }
        pros::delay(200);
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