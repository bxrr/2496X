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
}

void test_shoot()
{
    fw_spin(470);
    delay(2000);
    pid_index();
}

void turns()
{
    for(int i = 0; i < 10; i++) turn(90);
}

void nml_half_awp()
{
    const_vel(600, 150);
}

void ml_half_awp()
{
    arc_turn(180, 350);
}

void solo_awp()
{

}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("test shoot", test_shoot),
    Auton("turns", turns),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
};


#endif