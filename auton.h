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
    drive_const(150, 80, 100);
    intake_dist(-300);
    delay(300);
    fw_spin(500);
    intake_dist(300);
    drive(-300, 1500);
    turn_to(-13, 1400);
    delay(500);
    index(2);
    turn_to(-130);
    intakeP.set(true);
    drive(900);
    fw_spin(440);
    intake_vel();
    intakeP.set(false);
    drive_const(200, 60, 1500);
    drive(400);
    turn_to(-29);
    drive(-350);
    index(3);
    fw_spin(450);
    arc_turn(180-25, 345, 1500);
    intakeP.set(true);
    drive(700);
    intakeP.set(false);
    intake_vel();
    delay(500);
    turn_to(-14);
    index(3);
}

void nml_safe_awp()
{
    fw_spin(440);
    intake_vel();
    drive(1400);
    turn_to(-141);
    index(3);
    intakeP.set(true);
}

void nml_half_awp()
{
    fw_spin(440);
    intake_vel();
    drive(1100);
    turn_to(-154);
    index(3);
    intakeP.set(true);
    arc_turn(-160, -260, 1500);
    intake_vel();
    drive(600);
    intakeP.set(false);
    delay(700);
    drive(-110);
    turn_to(-169.5);
    index(3);
    turn_to(174);
    drive(800);
    drive_const(240, 80, 300);
    intake_dist(-300);
    delay(300);
}

void solo_awp()
{
    
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("test shoot", test_shoot),
    Auton("turns", turns),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml safe awp", nml_safe_awp),
    Auton("nml half awp", nml_half_awp),
};


#endif