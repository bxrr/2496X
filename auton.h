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
    turn_to(90);
    fw_stop();
    
    drive(560);
    close_intake();
    intake_vel();
    delay(800);
   
    //shoot 3 discs
    turn_to(26);
    drive(-1425);
    intake_stop();
    fw_spin(300);
    turn_to(-6);
    shoot(3);
    fw_spin(-80);

    //get 3 on side of barrier
    turn_to(90);
    intake_vel();
    drive_const(1900,60);
    fw_spin(320);
    intakeP.set(true); //prevent 4disc
    drive(250);
    
    
    //shoot 3 at corner barrier
    turn_to(47);
    intake_stop();
    intakeP.set(false);
    // delay(300);
    shoot(3, -105);
    fw_spin(-80);
    
    //get 3 on side of barrier
    turn_to(180);
    fw_stop();
    intake_vel();
    drive_const(1550, 80);
    drive(515); // brian was here 
    fw_spin(300);
    
    //shoot 3 from barrier tape
    turn_to(98);
    shoot(3);
    turn_to(88);
    fw_stop();
    intake_stop();

    // get roller 1
    global_heading = 90;
    drive(2496);
    turn_to(180);
    intake_vel(127);
    drive_const(700, 127, 900);
    global_heading = 180;

    // get 3
    drive(-300);
    intake_stop();
    turn_to(0);
    open_intake();
    drive(600);
    close_intake();
    intake_vel();
    drive(350);
    turn_to(90);

    //get roller 2
    intake_vel(127);
    drive_const(600, 127, 800);
    drive_const(1400, 90, 800);
    global_heading = 90;

   
    // shoot
    drive(-275);
    turn_to(180);
    intake_stop();
    drive_const(-1020);
    fw_spin(300);
    drive(-1480);
    turn_to(170);
    shoot(3);

    // get 3 barrier
    turn_to(-90);
    intake_vel();
    drive_const(1930,60);
    fw_spin(315);
    intakeP.set(true); //prevent 4disc
    drive(200);

    //shoot 3 corner shot
    turn_to(-133);
    intake_stop();
    intakeP.set(false);
    shoot(3, -105);
    fw_spin(-80);

    // //Get 3 in a line
    // intake_vel();
    // drive(100);
    // turn_to(-45);
    // drive(1700);

    // //shoot 3
    // fw_spin(315);
    // turn_to(-106);
    // drive(-1000);
    // shoot(3);

    //get 3 along barrier
    turn_to(180);
    intake_vel();
    drive_const(-2000,60);
    intake_stop();
    fw_spin(315);
    turn_to(-85);
    shoot(3);


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