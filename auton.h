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
    index(2, 500, 2000);
    fw_stop();

    intakeP.set(true);
    turn_to(-130, 1400);
    intake_vel();
    drive(1170);
    intakeP.set(false);
    delay(600);
    fw_spin(470);
    drive(-530);
    turn_to(-13);
    intake_vel(0);
    intakeP.set(true);
    index(3, 500, 2000);
    fw_stop();

    turn_to(135);
    intake_vel();
    drive(410);
    intakeP.set(false);
    delay(600);
    fw_spin(465);
    drive(-400);
    turn_to(-15);
    intake_vel(0);
    intakeP.set(true);
    index(3, 500, 2000);
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
    // match loader 1
    fw_spin(350);
    turn_to(-5);
    for(int i = 0; i < 10; i++)
    {
        intake_vel(-127);
        delay(300);
        intake_vel(127);
        delay(300);
    }
    fw_stop();

    // get 3 stack and shoot
    turn_to(0);
    drive(700);
    turn_to(90);
    intakeP.set(true);
    intake_vel();
    drive(1400);
    intakeP.set(false);
    delay(600);

    turn_to(135);
    drive(1000);
    intake_stop();
    fw_spin(350);
    turn_to(26);
    intakeP.set(true);
    shoot();
    fw_stop();

    // get 3 and shoot
    turn_to(135);
    intakeP.set(false);
    intake_vel();
    drive(3000);
    drive(-2000);
    intake_stop();
    fw_spin(350);
    turn_to(58);
    intakeP.set(true);
    shoot();
    fw_stop();

    // get roller 1
    turn_to(135);
    drive(4000);
    turn_to(180);
    roller();

    // get 3 more discs and do roller 2
    drive(-600);
    turn_to(45);
    intake_vel();
    drive(600);
    intakeP.set(false);
    delay(600);
    drive(800);
    intake_stop();
    turn_to(90);
    drive(500);
    roller();

    // match loads 2
    drive(-100);
    turn_to(180);
    drive(-1200);
    fw_spin(350);
    turn_to(175);
    for(int i = 0; i < 11; i++)
    {
        intake_vel(-127);
        delay(300);
        intake_vel(127);
        delay(300);
    }

    // REPEATS START
    // get 3 stack and shoot
    turn_to(0);
    drive(700);
    turn_to(90);
    intakeP.set(true);
    intake_vel();
    drive(1400);
    intakeP.set(false);
    delay(600);

    turn_to(135);
    drive(1000);
    intake_stop();
    fw_spin(350);
    turn_to(26);
    intakeP.set(true);
    shoot();
    fw_stop();

    // get 3 and shoot
    turn_to(135);
    intakeP.set(false);
    intake_vel();
    drive(3000);
    drive(-2000);
    intake_stop();
    fw_spin(350);
    turn_to(58);
    intakeP.set(true);
    shoot();
    fw_stop();

    // get roller 1
    turn_to(135);
    drive(4000);
    turn_to(180);
    roller();

    // END OF REPEAT
    // get 3 more discs and do roller 2
    drive(-1800);
    turn_to(-90);
    drive(1500);
    roller();
    turn_to(-135);
    drive(-1000);
    turn_to(-45);
    
    // end game shoot!!!
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