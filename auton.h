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
    return;
}

void mload_side()
{
    recover = true;
    flywheel_target = 455;
    chas.spin_dist(30, 127, 100);
    intake_dist(450);
    delay(350);
    drive(-100);
    turn_to(-5);
    delay(200);
    index(2, 500, 5000);
    flywheel_target = 430;
    turn_to(-120);
    intake_vel();
    drive(2800);
    turn_to(-50);
    intake_vel(0);
    index(3);
    flywheel_target = 0;
}

void test_drive()
{
    drive(200);
    drive(-500);
    drive(1000);
    drive(-2500);
}

void test_turn()
{
    turn(90);
    turn_to(-90);
    turn_to(0);
    turn_to(45);
    turn_to(15);
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

    // drive(1400);
    // turn_to(-90);
    // chas.spin_dist(50);
    // intake_dist(500);

    // turn_to(90);
    // intake_vel(127);
    // drive(700);
    // intake_vel(0);
    // turn_to(0);
    // drive(600);
    // intake_dist(500);

    // turn_to(-90);
    // flywheel_target = 390;
    // drive(-1500);
    // intake_dist(-1100);
    // delay(600);
    
    // drive(1500);
    // turn_to(-135);
    // intake_vel(127);
    // drive(1800);
    // intake_vel(0);
    // turn_to(-45);
    // intake_dist(-1100);
    // delay(600);

    // turn_to(-135);
    // drive(700);
    // turn_to(90);
    // drive(600);
    // turn_to(180);
    // for(int i = 0; i < 11; i++)
    // {
    //     delay(800);
    //     intake_dist(-310);
    // }

    // drive(1400);
    // turn_to(-90);
    // chas.spin_dist(50);
    // intake_dist(500);

    // turn_to(90);
    // intake_vel(127);
    // drive(700);
    // intake_vel(0);
    // turn_to(0);
    // drive(600);
    // intake_dist(500);

    // turn_to(-90);
    // flywheel_target = 390;
    // drive(-1500);
    // intake_dist(-1100);
    // delay(600);
    // drive(1400);
    // turn_to(135);
    // drive(180);
    // //endgame
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("m_load_side", mload_side),
    Auton("test drive", test_drive),
    Auton("test turn", test_turn),
    Auton("longshot", longshot),
    Auton("skills", skills),
};


#endif