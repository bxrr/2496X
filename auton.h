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
    fw_recover(true);
    fw_spin(500);
    chas.spin_dist(30, 127, 100);
    intake_dist(220);
    delay(250);
    drive(-200, 1000);
    turn_to(-5.5, 1500);
    delay(200);
    index(2, 500, 2000);

    fw_spin(430);
    delay(200);
    turn_to(-135);
    intake_vel();
    drive(2700);
    turn_to(-29);
    intake_vel(0);
    delay(200);
    index(3, 300, 7000);
    fw_stop();
    turn_to(-137.2);
    intake_vel();

    drive(1950);
    intake_vel(0);
    arc_turn(43.2, 510, 1000);
    fw_spin(455);
    intake_dist(450);
    delay(350);

    // possibly shoot 3 more discs
    drive(-70);
    turn_to(-81.4);
    index(3, 300, 7000);
    fw_stop();
}

void test_drive()
{
    drive(500);
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