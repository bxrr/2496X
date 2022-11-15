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
    fw_spin(520);
    chas.spin(50);
    delay(100);
    intake_dist(-200);
    delay(200);
    drive(-400, 800);
    turn_to(-5.2, 700);
    delay(100);
    index(2, 600, 3000);
    delay(100);

    fw_spin(435);
    intakeP.set(true);
    turn_to(-127, 2200);

    // start intake
    intake_vel();

    // intake discs
    drive(1150, 1600);
    intakeP.set(false);
    delay(1000);

    turn_to(-22, 1700);
    intake_vel(0);
    delay(100);
    index(3, 700, 4000);
    delay(100);
    fw_stop();

    turn_to(-135, 2000);
    drive_const(3500);
    arc_turn(90, 500, 900);
    chas.spin(50);
    delay(250);
    intake_dist(-300);
    delay(300);
    chas.stop();
}

void ml_half_awp()
{
    fw_spin(500);
    chas.spin(50);
    delay(100);
    intake_dist(-200);
    delay(200);
    drive(-400, 1000);
    turn_to(-5.2, 1000);
    delay(100);
    index(2, 1000, 4000);
    delay(200);

    fw_spin(435);
    intakeP.set(true);
    turn_to(-127, 3000);

    // start intake
    intake_vel();

    // intake discs
    drive(1150, 1600);
    intakeP.set(false);
    delay(1000);

    turn_to(-22, 2000);
    intake_vel(0);
    delay(50);
    index(3, 800, 4000);
    delay(400);
    fw_stop();
}

void nml_half_awp()
{
    fw_spin(500);
    drive(1300, 1500);
    turn_to(97, 1500);
    delay(100);
    index(2, 800, 4000);
    delay(100);
    
    fw_spin(450);
    turn_to(90, 1000);
    chas.spin(50);
    delay(150);
    intake_dist(-200);
    delay(200);

    drive(-400, 1000);
    turn_to(-139, 1500);
    intake_vel();
    drive(2800, 3300);

    turn_to(135, 2200);
    delay(100);
    index(3, 800, 4000);
    delay(100);
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
    Auton("skills", skills),
};


#endif