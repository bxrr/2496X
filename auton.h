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
    fw_spin(490);
    index(3, 500, 15000);
}

void arc()
{
    arc_turn(90, 650, 2000);
}

void solo_awp()//pmuller@tustin.k12.ca.us
{
    drive(100, 200);
    fw_spin(480);
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
    turn_to(-13.5);
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
    drive(100, 200);
    fw_spin(480);
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
    drive(-350);
    turn_to(-10);
    intake_vel(0);
    intakeP.set(true);
    index(3, 300, 2500);
    fw_stop();

    turn_to(132);
    intake_vel();
    drive(310);
    intakeP.set(false);
    delay(900);
    fw_spin(460);
    drive(-250);
    turn_to(-11.4);
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
    turn_to(90, 1000);
    drive(300, 500);
    intake_dist(-250);
    delay(400);

    drive(-150, 1000);
    turn_to(-143);
    intake_vel();
    drive(3550);

    fw_spin(435);
    turn_to(139.3, 2000);
    delay(500);
    intake_vel(0);
    index(3, 300, 2500);
    delay(900);
    fw_stop();
}

void skills()
{
    // match loader 1
    fw_spin(365);
    delay(800);
    for(int i = 0; i < 3; i++)
    {
        intake_vel(-127);
        delay(300);
        intake_vel(127);
        delay(300);
    }
    fw_stop();

    // get 3 stack and shoot
    drive(650);
    turn_to(90);
    intakeP.set(true);
    intake_vel();
    delay(200);
    drive(800);
    intakeP.set(false);
    delay(600);
    drive(450);

    turn_to(135);
    drive(500);
    intakeP.set(true);
    intake_stop();
    fw_spin(355);
    turn_to(28);
    shoot();
    fw_stop();
    intakeP.set(false);

    // get 3 and shoot
    turn_to(135);
    intake_vel();
    drive(2850);
    delay(300);
    turn_to(80);
    fw_spin(345);
    intake_stop();
    intakeP.set(true);
    drive(-800);
    shoot();
    fw_stop();

    // get three stack
    drive(1700);
    intake_vel();
    intakeP.set(false);
    turn_to(90);
    drive(700);

    // do roller 1
    turn_to(180);
    intakeP.set(true);
    drive_const(500);
    intake_stop();
    drive(500);
    roller();

    // do roller 2
    drive(-1000);
    turn_to(90);
    drive(700, 1200);
    roller();

    // match loads 2
    drive(-200);
    turn_to(190);
    intake_vel();
    drive(-2300, 2000);
    drive(200);
    turn_to(175);
    fw_spin(350);
    delay(1000);
    intake_stop();
    for(int i = 0; i < 4; i++)
    {
        intake_vel(-127);
        delay(400);
        intake_vel(127);
        delay(400);
    }

    // REPEATS START
    // get 3 stack and shootshoot
    turn_to(180);
    drive(600);
    turn_to(-90);
    intakeP.set(true);
    intake_vel();
    drive(950);
    intakeP.set(false);
    delay(600);
    drive(400);

    turn_to(-45);
    intakeP.set(true);
    drive(500);
    intake_stop();
    fw_spin(350);
    turn_to(-153);
    shoot();
    fw_stop();
    intakeP.set(false);

    // get 3 and shoot
    turn_to(-45);
    intake_vel();
    drive(2650);
    delay(300);
    turn_to(-102);
    fw_spin(360);
    intake_stop();
    intakeP.set(true);
    drive(-1100);
    shoot();
    fw_stop();

    // end of repeat-shoot 3 stack
    drive(1100);
    turn_to(-90);
    intake_vel();
    drive(700);
    intakeP.set(false);
    delay(800);
    drive(-700);
    turn_to(-102);
    intakeP.set(true);
    fw_spin(360);
    drive(-1100);
    intake_stop();
    shoot();
    fw_stop();

    // get roller 3
    drive(1100);
    turn_to(-90);
    drive(1800);
    roller();
    drive(-1100);
    turn_to(0);
    drive(1100);
    roller();
    drive(-1300);
    turn_to(-45);
    drive(800);

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