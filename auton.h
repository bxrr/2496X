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
    fw_spin(320);
    delay(1000);
    shoot(3); 
   
    //get 3 on side of barrier
    turn_to(94, 3000);
    intake_vel();
    drive_const(1700, 60);
    fw_spin(325);
    intakeP.set(true); //prevent 4disc
    drive(300, 1000);
    
    // shoot 3 at corner barrier
    turn_to(47, 1400);
    intake_stop();
    shoot(3);

    // get line
    intakeP.set(false);
    intake_vel();
    drive(340);
    turn_to(135);
    fw_spin(325);
    drive(1800);

    // shoot
    turn_to(80, 1100);
    drive(-1000);
    shoot(3);

    // get 3 stack
    // turn_to(78);
    intakeP.set(true);
    drive(1680, 5000);
    // turn_to(76);
    intake_vel();
    intakeP.set(false);
    delay(550);
    drive(600);

    // roller 1
    turn_to(89);
    intake_stop();
    intakeP.set(true);
    drive_const(950, 115);
    drive_const(400, 40, 300);
    roller(430);
    drive(-670);

    // roller 2
    turn_to(180);
    drive(1050);
    drive_const(500, 40, 300);
    roller(430);
    drive(-400);
    // drive(10000000000000); frfr grrr hello from the other side this is evana helllo from the other side i must have called you a thousand times to tell you that im sorry for bla blah idrk any of the lyrics...if you delete this then. nothing would happen! 
    
    // shoot 3
    fw_spin(320);
    turn_to(180);
    drive(-3070, 6000);
    shoot(3);

    // get 2nd stack
    turn_to(-145);
    intakeP.set(true);
    intake_vel();
    drive(827);
    intakeP.set(false);
    delay(400);
    drive(300);

    // shoot 2nd stack
    fw_spin(320);
    turn_to(-168);
    drive(-900);
    shoot(3);

    // get 3 line again
    drive(930);
    turn_to(-50.5);
    intake_vel();
    drive(3700, 3000, 115);
    // shoot
    turn_to(-103);
    drive(-710);
    intake_stop(); // hi yousef, is that your wumpus? wampus? hippo pig monkey looking discord creature?
    shoot(3);

    // get 3 stack last
    turn_to(-103, 1000);
    intakeP.set(true);
    intake_vel();
    drive(1420, 4000);
    intakeP.set(false);
    delay(400);
    drive(300);

    // shoot last 3 
    drive(-1960, 4000);
    turn_to(-101.5, 1000);
    shoot(3);

    // roller 3
    turn_to(-91);
    fw_stop();
    intakeP.set(true);
    drive_const(2900, 110, 3000);
    drive_const(400, 40, 300);
    roller(430);
    drive(-790);

    // roller 4
    turn_to(0);
    drive_const(500, 105, 1500);
    drive_const(400, 40, 300);
    roller(430);
    drive(-730);

    // endgame
    turn_to(-45, 1000);
    drive(-200, 800);
}
void skills2()
{
    // shoot 2 preloads 
    fw_spin(349);
    delay(1000);
    shoot(3, -86); //was set to -40
    
    //get 3 discs
    fw_stop();
    open_intake();
    turn_to(90, 2000);
    
    drive(550, 2000);
    close_intake();
    intake_vel();
    delay(750);
    // drive(100, 2000);
    // delay(100);
    // drive(-90, 2000);
   
    //shoot 3 discs
    turn_to(30.8, 1200);
    drive(-1530, 1500);
    intake_stop();
    fw_spin(330);
    turn_to(-4, 1000);
    shoot(3);
    fw_stop();

    //get 3 on side of barrier
    turn_to(90, 1000);
    intake_vel();
    drive_const(1865, 60);
    fw_spin(345);
    intakeP.set(true); //prevent 4disc
    drive(225, 1000);
    
    
    //shoot 3 at corner barrier
    turn_to(47, 1000);
    intake_stop();
    intakeP.set(false);
    // delay(300);
    shoot(3);
    fw_stop();
    
    //get 3 on other side of barrier
    turn_to(-178.5, 1000);
    fw_stop();
    intake_vel();
    drive_const(1800, 80);
    drive(350, 1000); // brian was here 
    fw_spin(330);
    
    //shoot 3 from barrier tape
    open_intake();
    turn_to(96, 1000);
    shoot(3);
    fw_stop();
    turn_to(84.3, 1000);
    close_intake();
    intake_stop();

    // get roller 1
    intake_vel(-127);
    drive(2400, 3000);
    fw_stop();
    turn_to(180, 1600);
    intake_stop();
    drive_const(750, 50, 750);
    roller(430);

    // get 3
    delay(200);
    drive(-270, 1000);
    intake_stop();
    turn_to(-4, 2000);
    open_intake(); // other brian was here
    intake_vel();
    drive(500, 1200);
    close_intake();
    intake_vel();
    delay(750);
    drive(475, 1400);
    turn_to(90, 1500);

    //get roller 2
    //intake_vel(127);
    open_intake();
    drive(800, 2600, 100);
    intake_stop();
    delay(200);
    drive_const(150, 50, 750);
    roller(430);
    delay(200);
   
    // shoot
    drive(-320, 1500);
    turn_to(177, 2000);
    fw_spin(330);
    drive(-2000, 5000);
    turn_to(175, 2000);
    shoot(3);

    // get 3 stack
    fw_stop();
    turn_to(-138, 3000);
    // open_intake();
    intake_vel();
    drive(970, 4000);
    close_intake();
    delay(500);
    drive(150);
    fw_spin(330);
    turn_to(-169, 3000);
    drive(-900);
    turn_to(-168, 3000);
    // turn_to(175, 3000);
    shoot(3);


    // get line
    turn_to(-90);
    fw_stop();
    intake_vel();
    drive(1600);
    turn_to(-47);
    drive(2500);
    fw_spin(340);
    turn_to(-97);
    drive(-1100);
    turn_to(-97);
    shoot(3);
    fw_stop();

    intake_vel();
    turn_to(-95);
    drive(2850, 4000);
    intake_stop();
    open_intake();
    drive_const(300, 50, 400);
    roller(430);
    delay(200);
    drive(-500, 1500);
   
    // roller 4 + expand
    turn_to(0);
    drive(450);
    drive_const(200, 50, 500);
    roller(430);
    delay(200);
    drive(-425, 1500);
    turn_to(-45);
    drive(-150);
    auton_expand();
   



    // // get 3 barrier
    // fw_spin(-70);
    // turn_to(-74, 800);
    // fw_stop();
    // intake_vel();
    // drive_const(2220, 60, 1500);
    // fw_spin(317);
    // intakeP.set(true); //prevent 4disc
    // drive(520, 700);

    // //shoot 3 corner shot
    // turn_to(-131.5, 700);
    // intake_stop();
    // shoot(3);
    // fw_spin(-85);

    // //Get 3 in a line
    // intakeP.set(false);
    // intake_vel();
    // drive(150, 400);
    // turn_to(-45, 700);
    // drive(1665, 1500);

    // //shoot 3
    // fw_spin(310);
    // turn_to(-126, 700);
    // intake_stop();
    // drive(-1550, 1200);
    // turn_to(-81, 700);
    // shoot(3);
    // fw_spin(-80);

    // //get 3 along barrier
    // turn_to(160, 800);
    // fw_stop();
    // intake_vel();
    // drive_const(1880, 80, 1500);
    // fw_spin(322);
    // drive(370, 560);
    // intake_stop();

    // // shoot 3 at corner
    // open_intake();
    // turn_to(-136, 650);
    // shoot(3, -90);

    // // get 3
    // fw_stop();
    // turn(-56, 700);
    // drive(-1120, 900);
    // turn_to(-90, 800);
    // drive(1810, 1200);
    // close_intake();
    // intake_vel();
    // delay(500);

    // // roller 3
    // drive_const(1000, 100, 700);
    // open_intake();
    // drive_const(1200, 40, 1100);
    // // intake_vel(-127);

    // //shoot 3
    // fw_spin(446);
    // drive_const(-300);
    // intake_stop();
    // drive(-1050,900);
    // turn_to(-103, 650);
    // shoot(3, -50);

    // // roller 4
    // turn_to(0, 700);
    // drive_const(600, 100, 800);
    // intake_vel();
    // fw_stop();
    // drive_const(1440, 40, 900);

    // // end game
    // drive(-1260, 900);
    // turn_to(-45, 700);
    // drive(520, 550);
    // glb::sideExpandP.toggle();
    // for(int i = 0; i < 5; i++)
    // {
    //     glb::expansionP.toggle();
    //     pros::delay(200);
    // }
}

void none()
{
    // roller(430);
    pid::global_heading = 0;
    imu.set_heading(0);
    delay(400);
    turn_to(5, 7000);
}

void test_shoot()
{
    fw_spin(460);
    delay(1500);
    pid_index();
    fw_stop();
}

void turns()
{
    turn_to(-180);
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
    // drive_const(100, 127, 200);
    roller(-310, 200);
    delay(150);
    // fw_spin(485);
    drive(-300, 700);

    // // shoot 2 preload
    // intake_vel();
    // turn_to(-11);
    // intake_stop();
    // // delay(800);
    // pid_index(3);
    // fw_stop();
    // // turn_to(4);
    
    // get 3 stack
    turn_to(-128, 1000);
    intakeP.set(true);
    intake_vel();
    fw_spin(462.2);
    drive(970, 1350);
    intakeP.set(false);
    delay(600);

    // shoot 3 stack
    turn_to(-22.4);
    intake_stop();
    pid_index(3);
    delay(150);
    // fw_stop();

    // get 2nd 3 stack
    turn_to(45);
    intakeP.set(true);
    drive(700);
    turn_to(140);
    intake_vel();
    // fw_spin(462.8);
    drive(400);
    intakeP.set(false);
    delay(600);

    // shoot 3 
    turn_to(-14, 1000);
    pid_index(3);
    delay(500);


    //ak fw_spin(500);_v
    // index(2, 1000);
    // index(2, 600);
    // delay(150);
    // open_intake();
    // turn_to(-135, 1500);
    // drive(1250, 1200);
    // intake_vel();
    // close_intake();
    // delay(800);
    // fw_spin(480);
    // turn_to(-22, 1100);
    // delay(500);
    // intake_stop();
    // index(3, 600);
    // turn_to(-135, 1100);
    // drive(750, 900);
    // open_intake();
    // turn_to(90, 1100);
    // drive(600, 900);
    // intake_vel();
    // close_intake();
    // delay(500);
    // fw_spin(490);
    // drive(-600, 900);
    // turn_to(-15, 1100);
    // index(3, 500);
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