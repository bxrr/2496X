#ifndef __AUTON__
#define __AUTON__

#include "main.h"
#include "global.h"
#include "pid.h"
#include "aut_func.h"
#include "lib/auton_obj.h"
#include <vector>
#include <string>

using namespace pros;
using namespace pid;
using namespace glb;
using namespace auf;

void none()
{
    pid::recover = true;
    return;
}

void longshot()
{
    flywheel_target = 530;
    delay(2500);
    for(int i = 0; i < 3; i++)
    {
        intake_dist(-310);
        delay(2000);
    }
    flywheel_target = 0;
}


void test_drive()
{
    drive(800);
    turn(50);
    turn_to(-40);
}

void skills()
{
    pid::recover = true;
    flywheel_target = 390;
    for(int i = 0; i < 8; i++)
    {
        delay(800);
        intake_dist(-310);
    }
    flywheel_target = 0;

    drive(1400);
    turn_to(-90);
    chas.spin_dist(50);
    intake_dist(500);

    turn_to(90);
    intake_vel(127);
    drive(700);
    intake_vel(0);
    turn_to(0);
    drive(600);
    intake_dist(500);

    turn_to(-90);
    flywheel_target = 390;
    drive(-1500);
    intake_dist(-1100);
    delay(600);
    
    drive(1500);
    turn_to(-135);
    intake_vel(127);
    drive(1800);
    intake_vel(0);
    turn_to(-45);
    intake_dist(-1100);
    delay(600);

    turn_to(-135);
    drive(700);
    turn_to(90);
    drive(600);
    turn_to(180);
    for(int i = 0; i < 11; i++)
    {
        delay(800);
        intake_dist(-310);
    }

    drive(1400);
    turn_to(-90);
    chas.spin_dist(50);
    intake_dist(500);

    turn_to(90);
    intake_vel(127);
    drive(700);
    intake_vel(0);
    turn_to(0);
    drive(600);
    intake_dist(500);

    turn_to(-90);
    flywheel_target = 390;
    drive(-1500);
    intake_dist(-1100);
    delay(600);
    drive(1400);
    turn_to(135);
    drive(180);
    //endgame
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("test fly", longshot),
    Auton("test drive", test_drive),

};


#endif