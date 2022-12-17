#ifndef __CHAS__
#define __CHAS__

#include "main.h"
#include <vector>
#include <array>


class Chassis
{
private:
    std::vector<pros::Motor> left_motors;
    std::vector<pros::Motor> right_motors;

public:
    Chassis(std::vector<int> left_motor_ports, std::vector<int> right_motor_ports, 
    pros::motor_gearset_e gearset=pros::E_MOTOR_GEARSET_06, bool reverse_spin=false)
    {
        for(int port : left_motor_ports)
            left_motors.push_back(pros::Motor(abs(port), gearset, port < 0 ? reverse_spin : !reverse_spin));
        for(int port : right_motor_ports)
            right_motors.push_back(pros::Motor(abs(port), gearset, port < 0 ? !reverse_spin : reverse_spin));
    }

    void spin_left(double speed)
    {
        for(pros::Motor motor : left_motors)
            motor.move(speed);
    }

    void spin_right(double speed)
    {
        for(pros::Motor motor : right_motors)
            motor.move(speed);
    }

    void spin(double speed)
    {
        spin_left(speed);
        spin_right(speed);
    }

    void stop()
    {
        spin(0);
    }

    void reset()
    {
        for(pros::Motor motor : left_motors)
            motor.tare_position();
        for(pros::Motor motor : right_motors)
            motor.tare_position();
    }

    double left_pos()
    {
        double sum = 0;
        for(pros::Motor motor : left_motors)
        {
            sum += motor.get_position();
        }
        return sum / left_motors.size();
    }

    double right_pos()
    {
        double sum = 0;
        for(pros::Motor motor : right_motors)
        {
            sum += motor.get_position();
        }
        return sum / left_motors.size();
    }
    
    double pos()
    {
        return (left_pos() + right_pos()) / 2;
    }

    double left_speed()
    {
        double sum = 0;
        for(pros::Motor motor : left_motors)
        {
            sum += motor.get_actual_velocity();
        }
        return sum / left_motors.size();
    }

    double right_speed()
    {
        double sum = 0;
        for(pros::Motor motor : right_motors)
        {
            sum += motor.get_actual_velocity();
        }
        return sum / right_motors.size();
    }

    double speed()
    {
        return (left_speed() + right_speed()) / 2;
    }

    double temp()
    {
        double sum = 0;
        for(pros::Motor motor : left_motors)
            sum += motor.get_temperature();
        for(pros::Motor motor : right_motors)
            sum += motor.get_temperature();

        return sum / (left_motors.size() + right_motors.size());
    }

    void spin_dist(double distance, double speed=127, int timeout=3000)
    {
        int time = 0;
        double start_pos = pos();
        double target = start_pos + distance;

        while((distance < 0 ? pos() > target : pos() < target) && time < timeout)
        {
            spin(distance / fabs(distance) * abs(speed));
            pros::delay(10);
            time += 10;
        }
        stop();
    }
};

#endif