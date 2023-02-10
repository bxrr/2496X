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

void skills()
{
    // shoot 2 preloads 
    fw_spin(320);
    delay(1000);
    shoot(3, -90);
    
    //get 3 discs
    fw_spin(-80);
    open_intake();
    turn_to(90, 700);
    fw_spin(0);
    
    drive(560, 800);
    close_intake();
    intake_vel();
    delay(800);
   
    //shoot 3 discs
    turn_to(26, 700);
    drive(-1450, 1200);
    intake_stop();
    fw_spin(310);
    turn_to(-6, 600);
    shoot(3);
    fw_spin(-80);

    //get 3 on side of barrier
    turn_to(90, 700);
    intake_vel();
    drive_const(1900, 60);
    fw_spin(310);
    intakeP.set(true); //prevent 4disc
    drive(230, 400);
    
    
    //shoot 3 at corner barrier
    turn_to(47, 500);
    intake_stop();
    intakeP.set(false);
    // delay(300);
    shoot(3, -107);
    fw_spin(-80);
    
    //get 3 on side of barrier
    turn_to(180, 850);
    fw_stop();
    intake_vel();
    drive_const(1715, 80);
    drive(350, 500); // brian was here 
    fw_spin(295);
    
    //shoot 3 from barrier tape
    turn_to(98, 700);
    shoot(3);
    turn_to(85, 550);
    fw_stop();
    intake_stop();

    // get roller 1
    drive(2433, 1800);
    turn_to(180, 800);
    intake_vel(127);
    drive_const(700, 50, 900);
    global_heading = 180;

    // get 3
    drive(-300, 500);
    intake_stop();
    turn_to(0, 1200);
    open_intake();
    drive(600, 800);
    close_intake();
    intake_vel();
    drive(350, 550);
    turn_to(90, 700);
    open_intake();

    //get roller 2
    intake_vel(127);
    drive_const(600, 90, 800);
    drive_const(1340, 40, 900);
    global_heading = 90;
   
    // shoot
    drive(-285, 550);
    turn_to(180, 700);
    intake_stop();
    drive_const(-1020, 127, 1250);
    fw_spin(300);
    drive(-1400, 1150);
    turn_to(173, 700);
    shoot(3);
    close_intake();

    // get 3 barrier
    fw_spin(-70);
    turn_to(-90, 800);
    fw_stop();
    intake_vel();
    drive_const(1930,75, 1500);
    fw_spin(315);
    intakeP.set(true); //prevent 4disc
    drive(200, 400);

    //shoot 3 corner shot
    turn_to(-133, 700);
    intake_stop();
    shoot(3, -105);
    fw_spin(-85);

    //Get 3 in a line
    intakeP.set(false);
    intake_vel();
    drive(150, 400);
    turn_to(-45, 700);
    drive(1700, 1500);

    //shoot 3
    fw_spin(318);
    turn_to(-125, 700);
    drive(-1590, 1200);
    turn_to(-84, 700);
    shoot(3);

    //get 3 along barrier
    turn_to(180, 750);
    intake_vel();
    drive_const(1840, 80, 1500);
    fw_spin(315);
    drive(250, 500);
    intake_stop();

    // shoot 3
    turn_to(-132, 600);
    shoot(3);

    // get 3
    fw_stop();
    turn_to(180, 700);
    drive(-1250, 1200);
    turn_to(-90, 700);
    open_intake();
    drive(2100, 1600);
    close_intake();
    intake_vel();
    delay(800);

    // shoot 3
    // fw_spin(310);
    // drive(-1900);
    // shoot(3);

    // roller 3
    // drive_const(2000, 127, 1500);
    // intake_vel();
    drive_const(800, 100, 700);
    open_intake();
    drive_const(1200, 40, 1100);
    global_heading = -90;
    // intake_vel(-127);

    //shoot 3
    fw_spin(450);
    drive_const(-300);
    intake_stop();
    drive(-400,700);
    turn_to(-101, 650);
    shoot(4,-75);

    // roller 4
    turn_to(0, 700);
    drive_const(600, 100, 800);
    intake_vel();
    fw_stop();
    drive_const(1340, 40, 900);
    global_heading = 0;

    // end game
    drive(-850, 800);
    turn_to(-45, 800);
    for(int i = 0; i < 10; i++)
    {
        glb::expansionP.toggle();
        glb::sideExpandP.toggle();
        pros::delay(200);
    }
}

void none()
{
    intake_vel();
    turn_to(25);
    drive(-1500);
}

void test_shoot()
{
    fw_spin(460);
    delay(1800);
    index();
}

void turns()
{
    turn_to(180);
    turn_to(0);
    delay(500);
    turn_to(135);
    turn_to(0);
    delay(500);
    turn_to(90);
    turn_to(0);
    delay(500);
    turn_to(45);
    turn_to(0);
    delay(500);
    turn_to(30);
    turn_to(0);
    delay(500);
    turn_to(9);
    turn_to(0);
    delay(500);
}

void drives()
{
    drive(3000);
    drive(-3000);
    delay(500);
    drive(1000);
    drive(-1000);
    delay(500);
    drive(500);
    drive(-500);
    delay(500);
    drive(250);
    drive(-250);
    delay(500);
    drive(100);
    drive(-100);
}

void solo_awp()//pmuller@tustin.k12.ca.us
{
    drive_const(100, 70, 200);
    fw_spin(445);
    intake_dist(-200);
    delay(200);
    drive(-200, 800);
    intake_dist(300);
    delay(100);
    // index(2, 300, 1800);
    fw_spin(395);

    intakeP.set(true);
    turn_to(-127.5, 1500);
    intake_vel();
    drive(1200, 1500);
    intakeP.set(false);
    delay(500);
    turn_to(-11.7);
    intake_vel(0);
    intakeP.set(true);
    // index(3, 300, 1800);
    fw_spin(333);

    turn_to(-132, 1600);
    intakeP.set(false);
    intake_vel(127);
    drive_const(4600);
    intake_vel(0);
    chas.spin_left(112);
    chas.spin_right(34);

    intakeP.set(true);
    delay(500);
    chas.spin(30);
    delay(300);
    intake_dist(-350);
    delay(500);
    chas.stop();
}

void ml_half_awp()
{
    drive_const(100, 127, 300);
    fw_spin(495);
    global_heading = 0;
    intake_dist(-200);
    delay(100);
    drive(-300);
    turn_to(-12);
    index(2, 750);
    delay(300);
}

void nml_half_awp()
{
    fw_spin(480);
    drive(1160, 1500);
    turn_to(99, 1500);
    // index(2, 300, 2500);
    
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
    // index(3, 300, 2500);
    delay(900);
    fw_stop();
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("skills", skills),
    Auton("none", none),
    Auton("test shoot", test_shoot),
    Auton("turns", turns),
    Auton("drives", drives),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
};


#endif