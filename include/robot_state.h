/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : robot_state.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 06.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_ROBOT_STATE_H
#define ROBOT_ROBOT_STATE_H

#include <vector>
#include <string>

#include "librobots/Robot.h"
#include "../robots/point.h"
#include "state.h"

class RobotState : public State {
    unsigned energy, power;

    bool isAlive = true;

    std::vector<std::string> updates;
public:

    class Robot *robot;
    RobotState(size_t id, class Robot *robot, Point coords, size_t fieldOfView, unsigned int energy, unsigned int power);

    std::vector<std::string> getUpdates();

    unsigned getPower();

    void setPower(unsigned power);

    unsigned getEnergy();

    void setEnergy(unsigned energy);

    bool getAliveState();

    void die();


    void addUpdate(const std::string &update);

    bool operator==(Point coords) const;
};

#endif //ROBOT_ROBOT_STATE_H
