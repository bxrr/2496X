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
    fw_spin(490);
    drive_const(30, 127, 100);
    intake_dist(420);
    delay(250);
    drive(-200, 1000);
    turn_to(-5.2, 1500);
    delay(300);
    index(2, 1300, 4000);
    delay(400);

    fw_spin(250);
    delay(200);
    turn_to(-128, 2200);

    // knock over discs

    // start intake
    intake_vel();
    intakeP.set(true);

    // intake discs
    
    drive_const(1900, 127);
    intakeP.set(false);
    drive(800, 1200);

    fw_spin(460);
    turn_to(-30.5, 1800);
    intake_vel(0);
    delay(100);
    index(3, 1200, 4000);
    delay(700);
    fw_stop();
    turn_to(-137.2, 1800);
    intake_vel();

    drive_const(2800, 127, 3000);
    drive(1350, 1800);
    intake_vel(0);

    turn_to(-90, 1800);
    
    drive_const(150, 50, 1000);
    intake_dist(1000);
    delay(2000);
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

void shooterize()
{
    fw_spin(460);
    drive_const(30, 127, 100);
    intake_dist(420);
    delay(250);
    drive(-200, 1000);
    turn_to(-5.2, 1500);
    delay(400);
    index(2, 700, 4000);
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("solo awp", solo_awp),
    Auton("shooterize", shooterize),
    Auton("test drive", test_drive),
    Auton("test turn", test_turn),
    Auton("test arc", test_arc),
    Auton("test all", test_all),
    Auton("skills", skills),
};


#endif