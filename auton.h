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

void solo_awp()
{
    fw_spin(460);
    drive_const(30, 127, 100);
    intake_dist(420);
    delay(250);
    drive(-200, 1000);
    turn_to(-5.5, 1500);
    delay(200);
    index(2, 1000, 3000);

    fw_spin(440);
    delay(200);
    turn_to(-135, 1800);
    intake_vel();
    drive_const(2100, 70);
    drive(600, 1800);
    turn_to(-30, 1800);
    intake_vel(0);
    delay(200);
    index(3, 1000, 4000);
    delay(200);
    fw_stop();
    turn_to(-137.2, 1800);
    intake_vel();

    drive_const(2800, 127, 3000);
    drive_const(500, 90, 600);
    intake_vel(0);
    arc_turn(48, 510, 1500);
    drive_const(300, 127, 1000);
    intake_dist(1000);
}

void test_drive()
{
    drive_const(1000);
}

void test_turn()
{
    turn(90);
    turn_to(-90);
    turn_to(0);
    turn_to(45);
    turn_to(15);
}

void test_all()
{
    drive(200);
    turn_to(-9.5);
    turn_to(-135);
    drive(3000);
    turn_to(0);
}

void test_arc()
{
    arc_turn(90, 1000);
}

void skills()
{
    fw_recover(true);
    fw_spin(390);
    index(9);
    fw_stop();
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("solo awp", solo_awp),
    Auton("test drive", test_drive),
    Auton("test turn", test_turn),
    Auton("test arc", test_arc),
    Auton("test all", test_all),
    Auton("skills", skills),
};


#endif