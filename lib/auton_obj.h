#ifndef __AUTON_OBJ__
#define __AUTON_OBJ__

#include "main.h"
#include <string>


typedef void(&fref)();
typedef void(*fptr)();

class Auton
{
private:
    std::string name;
    fptr auton;

public:
    Auton(std::string init_name, fref init_auton)
    {
        name = init_name;
        auton = init_auton;
    }

    void run() 
    {
        (*auton)();
    }

    std::string get_name()
    {
        return name;
    } 
};

#endif