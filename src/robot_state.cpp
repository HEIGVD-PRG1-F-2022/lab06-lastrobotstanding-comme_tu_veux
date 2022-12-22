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

#include "../include/robot_state.h"

RobotState::RobotState(size_t id, Point coords, Robot *robot, size_t fieldOfView, unsigned int energy, unsigned int power) {
    this->id = id;
    this->coords = coords;
    this->robot = robot;
    this->robot->setConfig(fieldOfView, fieldOfView, energy, power);
    this->energy = energy;
    this->power = power;
}

unsigned RobotState::getPower() {
    return power;
}

void RobotState::addUpdate(const std::string &update) {
    this->nextUpdates.push_back(update);
}

std::vector<std::string> RobotState::getCurrentUpdate() {
    return updates;
}

unsigned RobotState::getEnergy() {
    return this->energy;
}

void RobotState::setEnergy(unsigned int energy) {
    this->energy = energy;
}

size_t RobotState::getId() const {
    return this->id;
}
