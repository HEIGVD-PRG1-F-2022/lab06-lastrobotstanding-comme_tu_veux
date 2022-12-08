/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : robot_state.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 06.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include "robot_state.h"

RobotState::RobotState(Robot *robot, Point coords, size_t fieldOfView, unsigned int energy, unsigned int power) {
    this->robot = robot;
    this->robot->setConfig(fieldOfView, fieldOfView, energy, power);

    this->coords = coords;

    this->energy = energy;
    this->power = power;
}

bool RobotState::operator==(Point coords) const {
    return this->coords == coords;
}

Point RobotState::getCoords() {
    return coords;
}

unsigned RobotState::getPower() {
    return power;
}

void RobotState::addUpdate(const std::string &update) {
    this->updates.push_back(update);
}
