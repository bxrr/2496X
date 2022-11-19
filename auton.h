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

void solo_awp()//pmuller@tustin.k12.ca.us
{
    // 482.5
    fw_spin(485);
    chas.spin(50);
    delay(100);
    intake_dist(-200);
    delay(200);
    drive(-400, 1000);
    intake_dist(150);
    turn_to(-4.8, 800);
    delay(100);
    // 600
    index(2, 500, 2500);
    delay(200);

    fw_stop();
    intakeP.set(true);
    turn_to(-122, 1400);

    // start intake
    intake_vel(110);

    // intake discs
    drive(1100, 1100);//.Change the numbers to see what happens!
    intakeP.set(false);
    drive(200, 800);
    // fw_spin(463);
    fw_spin(471);

    // 14.2
    turn_to(-13, 1300);
    intake_vel(0);
    delay(50);
    index(3, 500, 3200);
    delay(300);
    fw_stop();

    turn_to(-132, 1500);
    intake_vel(127);
    drive_const(4250);
    delay(150);
    chas.spin_left(112);
    chas.spin_right(34);
    delay(480);
    intake_stop();
    chas.stop();
    delay(100);
    // chas.spin(50);
    // intake_dist(-300);
    // delay(300);
    chas.spin(50);
    delay(100);
    intake_dist(-300);
    delay(200);
    intake_stop();
    chas.stop();
}

void ml_half_awp()
{
    fw_spin(482.5);
    chas.spin(50);
    delay(100);
    intake_dist(-200);
    delay(200);
    drive(-400, 1000);
    intake_dist(150);//make sure to keep good documentation of your code through comments
    turn_to(-4.8, 1000);
    delay(100);
    index(2, 800, 4000);
    delay(200);

    fw_stop();
    intakeP.set(true);
    turn_to(-122, 3000);

    // start intake
    intake_vel(110);

    // intake discs
    drive(1100, 1300);
    intakeP.set(false);
    drive(200, 1000);
    fw_spin(463);

    turn_to(-14.2, 2000);
    intake_vel(0);
    delay(50);
    index(3, 800, 4000);
    delay(1200);
    fw_stop();
}

void nml_half_awp()
{
    fw_spin(493.8);
    drive(1200, 1500);
    turn_to(94.9, 1500);
    delay(100);
    index(2, 800, 4000);
    delay(200);
    
    fw_stop();
    turn_to(90, 1000);
    chas.spin(69);
    delay(320);
    intake_dist(-250);
    delay(300);

    drive(-250, 1000);
    turn_to(-149, 2400);
    intake_vel();
    drive(3550, 2400);

    fw_spin(463.6);
    turn_to(134.5, 2000);
    intake_vel(0);
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