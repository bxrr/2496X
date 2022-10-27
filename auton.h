#ifndef __AUTON__
#define __AUTON__

#include "main.h"
#include "global.h"
#include "pid.h"
#include "lib/auton_obj.h"
#include <vector>
#include <string>

using namespace pros;
using namespace pid;
using namespace glb;


void fly390()
{
    spin_flywheel();
    flywheel_target = 390;
    pros::delay(10000);
    flywheel_target = 0;
}


void test_drive()
{
    drive(800);
    turn(50);
    turn_to(-40);
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("test fly", fly390),
    Auton("test drive", test_drive),

};


#endif