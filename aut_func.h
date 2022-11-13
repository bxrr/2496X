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
    
    //red  340 < hue || hue < 20
    //blue 200 < hue && hue < 260
    int auto_roller(int color = 0, double chas_speed = 40, int timeout = 2000)
    {
        double hue = optical.get_hue();
        optical.set_led_pwm(100);
        int time = 0;
        bool stage = false;
        bool targetColor;
        // while (!(200 < hue && hue < 260) || !(340 < hue || hue < 20))
        //     pros::delay(2);

        while (time < timeout)
        {
            chas.spin(chas_speed);
            hue = optical.get_hue();
            if (!stage)
            {
                intake_vel(-80);
                if(((190 < hue && hue < 260) && !isRed) || ((340 < hue || hue < 20) && isRed))
                    stage = true;
            }
            // if (stage == 1)
            // {
            //     intake_vel(-100);
            //     if(((190 < hue && hue < 260) && isRed) || ((340 < hue || hue < 20) && !isRed))
            //         stage = 2;
            // }
            // if (stage == 2)
            // {
            //     intake_vel(-100);
            //     if(((190 < hue && hue < 260) && !isRed) || ((340 < hue || hue < 20) && isRed))
            //         stage = 3;
            // }
            if (stage)
            {
                intake_vel(0);
                break;
            }
            // if(((190 < hue && hue < 260) && !isRed) || ((340 < hue || hue < 20) && isRed))
            //     targetColor = true;
            // else
            //     targetColor = false;
            // if (targetColor == false)
            // {
            //     intake_vel(0);
            //     break;
            // }
            // else
            //     intake_vel(-100);

            pros::delay(1);
            time++;
        }
        chas.stop();
        optical.set_led_pwm(0);
        return isRed ? 1 : 2;
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
            if(abs(pid::fw_target() - pid::fw_speed()) < 2.5 && t_since_shot >= delay_ms)
            {
                intake_dist(-600);
                discs_shot++;
                t_since_shot = 0;
            }
            pros::delay(1);
            t_since_shot++;
            time++;
        }

        if(discs_shot < num_discs)
        {
            intake_dist(-1800);
            pros::delay(400);
        }
    }
}


#endif