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
    fw_spin(500);
    delay(15000);
}

void solo_awp()//pmuller@tustin.k12.ca.us
{
    fw_spin(485);
    drive(100, 200);
    intake_dist(-200);
    delay(200);
    drive(-200, 800);
    turn_to(-4.5, 800);
    intake_dist(200);
    index(2, 600, 2000);
    delay(200);
    fw_stop();

    intakeP.set(true);
    turn_to(-130, 1400);
    intake_vel();
    drive(1170);
    intakeP.set(false);
    delay(1500);
    fw_spin(460);
    turn_to(-14);
    fw_spin(470);
    intake_vel(0);
    intakeP.set(true);
    index(3, 500, 2000);
    delay(200);
    fw_stop();

    turn_to(-135, 1200);
    intakeP.set(false);
    intake_vel(127);
    drive_const(4500);
    delay(150);

    chas.spin_left(112);
    chas.spin_right(34);
    delay(480);
    intakeP.set(true);
    intake_stop();
    chas.stop();
    delay(100);
    // chas.spin(50);
    // intake_dist(-300);
    // delay(300);
    chas.spin(70);
    delay(400);
    intake_dist(-380);
    delay(200);
    intakeP.set(false);
    intake_stop();
    chas.stop();
}

void ml_half_awp()
{
    fw_spin(485);
    drive(100, 200);
    intake_dist(-200);
    delay(200);
    drive(-200, 800);
    turn_to(-4.3, 800);
    intake_dist(200);
    index(2, 600, 2000);
    fw_stop();

    intakeP.set(true);
    turn_to(-130, 1400);
    intake_vel();
    drive(1170);
    intakeP.set(false);
    fw_spin(465);
    delay(1500);
    turn_to(-14);
    intake_vel(0);
    intakeP.set(true);
    index(3, 600, 2000);
    fw_stop();

    turn_to(103.8);
    intake_vel();
    drive(510);
    intakeP.set(false);
    fw_spin(465);
    delay(800);
    drive(-400);
    turn_to(-15);
    intake_vel(0);
    intakeP.set(true);
    intake_vel(-127);
    delay(3000);
    intakeP.set(false);
    fw_stop();
}

void nml_half_awp()
{
    fw_spin(500);
    drive(1160, 1500);
    turn_to(99, 1500);
    delay(100);
    index(2, 600, 4000);
    delay(300);
    
    fw_stop();
    turn_to(90, 1000);
    chas.spin(60);
    delay(340);
    intake_dist(-260);
    delay(300);

    drive(-150, 1000);
    turn_to(-143.8, 1800);
    intake_vel();
    drive(3550, 2000);

    fw_spin(450);
    turn_to(139.3, 2000);
    intake_vel(0);
    delay(100);
    index(3, 600, 4000);
    delay(900);
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