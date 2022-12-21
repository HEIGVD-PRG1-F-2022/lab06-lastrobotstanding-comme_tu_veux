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

RobotState::RobotState(size_t id,
                       class Robot *robot,
                       Point coords,
                       size_t fieldOfView,
                       unsigned int energy,
                       unsigned int power) : State(id) {
    this->type = State::Type::Robot;
    this->robot = robot;
    this->robot->setConfig(fieldOfView, fieldOfView, energy, power);

    this->coords = coords;

    this->energy = energy;
    this->power = power;
}

bool RobotState::operator==(Point coords) const {
    return this->coords == coords;
}

unsigned RobotState::getPower() {
    return power;
}

void RobotState::addUpdate(const std::string &update) {
    this->updates.push_back(update);
}

std::vector<std::string> RobotState::getUpdates() {
    return updates;
}

unsigned RobotState::getEnergy() {
    return this->energy;
}

void RobotState::setEnergy(unsigned int energy) {
    this->energy = energy;
}

bool RobotState::getAliveState() {
    return this->isAlive;
}

void RobotState::die() {
    this->isAlive = false;
}


