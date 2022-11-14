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


#define ROLLER_DIST 420

void none()
{
    return;
}

void test_flywheel()
{
    fw_spin(495);
    index(3, 600, 4000);
}

void solo_awp()
{
    chas.spin(50);
    delay(200);
    intake_dist(-300);
    delay(400);
    fw_spin(485);
    drive(-200, 800);
    turn_to(-4.9, 900);
    delay(50);
    index(2, 600, 8000);
    delay(150);

    fw_spin(400);
    turn_to(-129, 2500);

    // start intake
    intake_vel();
    intakeP.set(true);

    // intake discs
    drive(1600, 1600);
    intakeP.set(false);
    drive(300, 600);

    fw_spin(450);
    turn_to(-21.2, 1500);
    intake_vel(0);
    delay(50);
    index(3, 500, 4000);
    delay(150);
    fw_stop();
}

void ml_half_awp()
{
    chas.spin(50);
    delay(400);
    intake_dist(-200);
    delay(200);
    fw_spin(485);
    drive(-200, 1000);
    turn_to(-4.9, 1000);
    delay(100);
    index(2, 600, 4000);
    delay(150);

    fw_spin(400);
    turn_to(-129, 2000);

    // start intake
    intake_vel();
    intakeP.set(true);

    // intake discs
    drive(1600, 1600);
    intakeP.set(false);
    drive(600, 1000);

    fw_spin(450);
    turn_to(-21.2, 1500);
    intake_vel(0);
    delay(50);
    index(3, 500, 4000);
    delay(150);
    fw_stop();
}

void nml_half_awp()
{
    drive(1300, 1600);
    turn_to(90, 1200);
    chas.spin(50);
    delay(500);
    intake_dist(-200);
    delay(400);
    fw_spin(485);
    drive(-200);
    turn_to(97.4);
    index(2, 1700, 8000);
    fw_stop();
}

void test_drive()
{
    drive(2800);
    drive(-1000);
    drive(-500);
}

void test_roller()
{
    drive_const(150, 50, 100);
    intake_dist(-1200);
    delay(1500);
    fw_spin(492);
    drive(-200, 800);
    turn_to(-4.9, 900);
    delay(50);
    index(2, 2200, 8000);
    delay(150);
    fw_stop();
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
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
    Auton("test drive", test_drive),
    Auton("test roller", test_roller),
    Auton("skills", skills),
};


#endif