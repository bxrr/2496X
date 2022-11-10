#ifndef __PISTON__
#define __PISTON__

#include "main.h"


class Piston
{
private:
    pros::ADIDigitalOut piston;
    bool status;
    int num_actuations;
    bool invert;

public:
    Piston(int port, bool init_status=false, bool invert=false) 
    : piston(port) 
    {
        set(init_status);
    }

    void set(bool extend)
    {
            piston.set_value(extend);
            status = extend;
    } 

    void toggle()
    {
        set(!status);
    }

    bool get_status()
    {
        return status;
    }
};

#endif