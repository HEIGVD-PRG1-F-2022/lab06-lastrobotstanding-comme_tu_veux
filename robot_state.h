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
#include "point.h"

class RobotState {
    Robot *robot;
    Point coords;
    unsigned energy, power;

    std::vector<std::string> updates;
public:
    RobotState(Robot *robot, Point coords, size_t fieldOfView, unsigned energy, unsigned power);

    Point getCoords();

    unsigned getPower();

    void addUpdate(const std::string &update);

    bool operator==(Point coords) const;
};

#endif //ROBOT_ROBOT_STATE_H
