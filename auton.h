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
}

void test_shoot()
{
    fw_spin(440);
    delay(1500);
    index(3);
}

void turns()
{
    turn(5);
    turn_to(0);
    turn_to(90);
    turn_to(0);
    turn_to(180);
    turn_to(21);
}

void ml_half_awp()
{
    drive_const(90, 80, 100);
    intake_dist(-300);
    delay(300);
    fw_spin(465);
    turn_to(0);
    drive(-900);
    intake_dist(300);
    turn_to(-61, 1400);
    index(2);
    intakeP.set(true);
    fw_spin(460);
    
    turn_to(90);
    drive(300);
    intake_vel();
    intakeP.set(false);
    delay(750);
    drive(-150);
    turn_to(-58);
    index(3);
    fw_spin(443);

    turn_to(-160);
    intakeP.set(true);
    drive(600);
    intakeP.set(false);
    intake_vel();
    drive(400);
    turn_to(-68);
    drive(-150);
    index(3);
}

void nml_half_awp()
{
    fw_spin(450);
    intakeP.set(true);
    drive(1150);
    intake_vel();
    intakeP.set(false);
    delay(700);
    drive(-150);
    turn_to(147);
    index(3);
    turn_to(180);
    intakeP.set(true);
    drive(1100);
    intakeP.set(false);
    intake_vel();
    delay(650);
    drive(-1100);
    turn_to(145);
    index(2);
    turn_to(120);
    drive(900);
    drive_const(90, 80, 100);
    intake_dist(-300);
    delay(300);
}

void solo_awp()
{
    drive_const(90, 80, 100);
    intake_dist(-300);
    delay(300);
    fw_spin(465);
    turn_to(0);
    drive(-900);
    intake_dist(300);
    turn_to(-62, 1400);
    index(2);
    intakeP.set(true);
    fw_spin(443);

    turn_to(180);
    intakeP.set(true);
    drive(600);
    intakeP.set(false);
    intake_vel();
    drive(400);
    turn_to(-68);
    drive(-150);
    index(3);

    turn_to(-180);
    intake_vel();
    drive(4500);
    drive_const(90, 80, 100);
    intake_dist(-300);
    delay(300);
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("test shoot", test_shoot),
    Auton("turns", turns),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
};


#endif