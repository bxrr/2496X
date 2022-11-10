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

void solo_awp()
{
    fw_spin(490);
    drive_const(30, 127, 100);
    intake_dist(ROLLER_DIST);
    delay(250);
    drive(-200, 1000);
    turn_to(-5.2, 1000);
    delay(100);
    index(2, 800, 4000);
    delay(250);

    fw_spin(250);
    turn_to(-128, 1600);

    // start intake
    intake_vel();
    intakeP.set(true);

    // intake discs
    drive_const(1550, 127);
    intakeP.set(false);
    drive(1150, 1500);

    fw_spin(460);
    turn_to(-30.5, 1500);
    intake_vel(0);
    delay(100);
    index(3, 800, 4000);
    delay(250);
    fw_stop();
    turn_to(-137.2, 1500);
    intake_vel();

    drive(3950, 2200);
    intake_vel(0);

    turn_to(-90, 1100);
    
    chas.spin(50);
    delay(200);
    intake_dist(ROLLER_DIST);
    delay(350);
    chas.stop();
}

void ml_half_awp()
{
    fw_spin(490);
    drive_const(30, 127, 100);
    intake_dist(ROLLER_DIST);
    delay(250);
    drive(-200, 1000);
    turn_to(-5.2, 1000);
    delay(100);
    index(2, 800, 4000);
    intakeP.set(true);
    delay(250);

    turn_to(165, 1500);
    drive(150, 1000);
    intake_vel();
    intakeP.set(false);
    turn_to(-5, 1600);
    index(3, 800, 4000);
    delay(250);

    turn_to(-128, 1600);

    intake_vel();
    intakeP.set(true);

    drive(1550, 1500);
    intakeP.set(false);
    delay(1000);
    turn_to(-30, 1200);
    index(3, 800, 4000);
    delay(200);
    fw_stop();
}

void nml_half_awp()
{
    fw_spin(490);
    drive(1000, 1500);
    turn_to(95.2, 1500);
    index(2, 800, 4000);
    delay(250);
    
    fw_spin(250);
    turn_to(90, 1000);
    drive_const(150, 40, 500);
    intake_dist(ROLLER_DIST);

    drive(-200);
    intakeP.set(true);
    turn_to(-90);
    intake_vel();
    drive(150, 1000);
    intakeP.set(false);
    delay(1000);

    fw_spin(480);
    drive(-150, 1000);
    turn_to(-84.8);
    index(3, 800, 4000);
    delay(250);
    
    fw_spin(250);
    turn_to(-135);
    intake_vel();
    drive(2880, 3000);
    fw_spin(450);
    turn_to(135);
    intake_vel(0);
    delay(100);
    index(3, 800, 4000);
    delay(250);
    fw_stop();
}

void test_drive()
{
    drive(2800);
    drive(-1000);
    drive(-500);
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
    Auton("skills", skills),
};


#endif