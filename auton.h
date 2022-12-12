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

//testing !
void none()
{
    fw_spin(485);
    delay(10000);
}

void test_shoot()
{
    fw_spin(485);
    index(3, 400, 3000)
    delay(500);
}

void test_const()
{
    fw_spin(485);
    index_const(3, 500);
}

void solo_awp()//pmuller@tustin.k12.ca.us
{
    drive_const(100, 200);
    fw_spin(482);
    intake_dist(-200);
    delay(200);
    drive(-200, 800);
    turn_to(-4, 800);
    intake_dist(300);
    delay(200);
    index(2, 300, 2000);
    fw_stop();

    intakeP.set(true);
    turn_to(-126, 2000);
    intake_vel();
    drive(1170);
    intakeP.set(false);
    delay(1000);
    fw_spin(463);
    turn_to(-13.8);
    intake_vel(0);
    intakeP.set(true);
    index(3, 300, 2500);
    fw_stop();

    turn_to(-131, 1500);
    intakeP.set(false);
    intake_vel(127);
    drive_const(4830);
    chas.spin_left(112);
    chas.spin_right(34);

    intakeP.set(true);
    delay(500);
    intake_stop();
    chas.stop();
    delay(100);
    chas.spin(60);
    delay(300);
    intake_dist(-400);
    delay(300);
    intakeP.set(false);
    intake_stop();
    chas.stop();
}

void ml_half_awp()
{
    drive_const(100, 127, 250);
    fw_spin(482);
    intake_dist(-200);
    delay(200);
    chas.stop();
    drive(-200, 800);
    turn_to(-4.3, 800);
    intake_dist(300);
    delay(200);
    index(2, 300, 2800);
    fw_stop();

    intakeP.set(true);
    turn_to(-127, 2000);
    intake_vel();
    drive(1170);
    intakeP.set(false);
    delay(1000);
    fw_spin(463);
    drive(-450);
    turn_to(-11);
    intake_vel(0);
    intakeP.set(true);
    index(3, 300, 3000);
    fw_stop();

    turn_to(129);
    intake_vel();
    drive(270);
    intakeP.set(false);
    delay(1500);
    intake_stop();
    fw_spin(452);
    drive(-250);
    turn_to(-13.5);
    intake_vel(0);
    index(3, 300, 2500);
    fw_stop();
}

void nml_half_awp()
{
    fw_spin(480);
    drive(1160, 1500);
    turn_to(99, 1500);
    index(2, 300, 2500);
    
    fw_stop();
    turn_to(90, 1300);
    drive_const(300, 70, 300);
    intake_dist(-250);
    delay(400);

    drive(-150, 1000);
    turn_to(-144);
    intake_vel();
    drive(3550);

    fw_spin(440);
    turn_to(138.9, 2000);
    delay(500);
    intake_vel(0);
    index(3, 300, 2500);
    delay(900);
    fw_stop();
}

void skills()
{
    // match loader 1
    fw_spin(350);
    delay(800);
    for(int i = 0; i < 3; i++)
    {
        intake_vel(-127);
        delay(200);
        intake_vel(127);
        delay(400);
    }
    fw_stop();

    
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("test shoot", test_shoot),
    Auton("test shoot", test_const),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
    Auton("skills", skills),
};


#endif