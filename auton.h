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
    fw_spin(455);
    chas.spin_dist(30, 127, 100);
    intake_dist(450);
    delay(350);
    drive(-150);
    turn_to(-9.5);
    delay(200);
    index(2, 500, 5000);

    fw_spin(450);
    turn_to(-131.5);
    intake_vel();
    drive(2560);
    turn_to(-35);
    intake_vel(0);
    delay(200);
    index(3, 500, 7000);
    fw_stop();
    turn_to(-136);
    intake_vel()

    drive(4500);
    intake_vel(0);
    turn_to(-90);
    fw_spin(455);
    chas.spin_dist(40, 127, 100);
    intake_dist(450);
    delay(350);

    // possibly shoot 3 more discs
    drive(-200);
    turn_to(-79);
    index(3, 500, 7000);
    fw_stop();
}

void test_drive()
{
    drive_ft(-2);
    drive_ft(8);
}

void test_turn()
{
    turn(90);
    delay(500);
    turn_to(-90);
    delay(500);
    turn_to(0);
    delay(500);
    turn_to(45);
    delay(500);
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
    Auton("test all", test_all),
    Auton("skills", skills),
};


#endif