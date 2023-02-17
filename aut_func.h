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

     void open_intake() 
     {
        intakeP.set(true);
    }
    
    void close_intake() 
    {
        intakeP.set(false);
    }

    void index(int num_discs=3, int ms_delay=600)
    {
        for(int i = 0; i < num_discs; i++)
        {
            intake_vel(-127);
            delay(140);
            intake_vel(0);
            if(i < num_discs-1) pros::delay(ms_delay);
        }
        pros::delay(200);
    }

    void shoot(int num_discs=3, double shoot_speed=-127)
    {
        delay(300);
        intake_vel(shoot_speed);
        int time = 0;
        while(time < num_discs * 90)
        {
            time += 10;
            pros::delay(10);
            if(glb::disc_sensor1.get() > 15) break;
        }
        if(time < num_discs * 220 - 100)
        {
            pros::delay(100);
        }
        intake_vel(0);
    }
}


#endif