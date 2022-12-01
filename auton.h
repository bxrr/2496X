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
    fw_spin(490);
    index(3, 500, 15000);
}

void arc()
{
    arc_turn(90, 650, 2000);
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
    fw_spin(490);
    drive(100, 200);
    intake_dist(-200);
    delay(200);
    drive(-200, 800);
    turn_to(-4.3, 800);
    intake_dist(200);
    index(2, 300, 2000);
    fw_stop();

    intakeP.set(true);
    turn_to(-130, 1400);
    intake_vel();
    drive(1170);
    intakeP.set(false);
    delay(600);
    fw_spin(475);
    drive(-530);
    turn_to(-10);
    intake_vel(0);
    intakeP.set(true);
    index(3, 300, 2500);
    fw_stop();

    turn_to(135);
    intake_vel();
    drive(340);
    intakeP.set(false);
    delay(600);
    fw_spin(470);
    drive(-340);
    turn_to(-9);
    intake_vel(0);
    intakeP.set(true);
    index(3, 300, 2500);
    intakeP.set(false);
    fw_stop();
}

void nml_half_awp()
{
    fw_spin(490);
    drive(1160, 1500);
    turn_to(99, 1500);
    index(2, 500, 4000);
    
    fw_stop();
    turn_to(90, 1000);
    drive(100, 250);
    intake_dist(-250);
    delay(250);

    drive(-150, 1000);
    turn_to(-143.8, 1800);
    intake_vel();
    drive(3550, 2000);

    fw_spin(455);
    turn_to(139.3, 2000);
    intake_vel(0);
    delay(100);
    index(3, 500, 4000);
    delay(900);
    fw_stop();
}

void skills()
{
    // match loader 1
    fw_spin(350);
    turn_to(-5);
    for(int i = 0; i < 11; i++)
    {
        intake_vel(-127);
        delay(300);
        intake_vel(127);
        delay(300);
    }
    fw_stop();

    // get 3 stack and shoot
    turn_to(0);
    drive(500);
    turn_to(90);
    intakeP.set(true);
    intake_vel();
    drive(1200);
    intakeP.set(false);
    delay(600);

    turn_to(135);
    intakeP.set(true);
    drive(500);
    intake_stop();
    fw_spin(350);
    turn_to(26);
    shoot();
    fw_stop();
    intakeP.set(false);

    // get 3 and shoot
    turn_to(135);
    intake_vel();
    drive(2500);
    turn_to(81);
    fw_spin(350);
    intake_stop();
    intakeP.set(true);
    drive(-1400);
    shoot();
    fw_stop();

    // get three stack
    drive(1400);
    turn_to(90);
    drive(800);
    intake_vel();
    intakeP.set(false);
    delay(300);
    drive(250);

    // do roller 1
    turn_to(180);
    intakeP.set(true);
    drive(1200);
    intake_stop();
    roller();

    // do roller 2
    drive(-1200);
    turn_to(90);
    drive(1200);
    roller();

    // match loads 2
    drive(-70);
    turn_to(180);
    drive(-1200);
    fw_spin(350);
    turn_to(175);
    for(int i = 0; i < 12; i++)
    {
        intake_vel(-127);
        delay(300);
        intake_vel(127);
        delay(300);
    }

    // REPEATS START
    // get 3 stack and shootshoot
    turn_to(180);
    drive(500);
    turn_to(-90);
    intakeP.set(true);
    intake_vel();
    drive(1200);
    intakeP.set(false);
    delay(600);

    turn_to(-45);
    drive(500);
    intake_stop();
    fw_spin(350);
    turn_to(26);
    shoot();
    fw_stop();

    // get 3 and shoot
    turn_to(-45);
    intake_vel();
    drive(2500);
    turn_to(-99);
    fw_spin(350);
    intake_stop();
    intakeP.set(true);
    drive(-1400);
    shoot();
    fw_stop();

    drive(1400);
    turn_to(-90);
    drive(800);
    intake_vel();
    intakeP.set(false);

    // end of repeat-shoot 3 stack
    delay(600);
    turn_to(-94);
    intakeP.set(true);
    fw_spin(350);
    drive(-1900);
    intake_stop();
    shoot();
    fw_stop();

    // get roller 3
    drive(1800);
    turn_to(-90);
    drive(1400);
    roller();
    drive(-1200);
    turn_to(0);
    drive(1200);
    roller();
    drive(-1300);
    turn_to(-45);
    drive(500);

    // end game shoot!!!
    expansionP.toggle();
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("arc", arc),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
    Auton("skills", skills),
};


#endif