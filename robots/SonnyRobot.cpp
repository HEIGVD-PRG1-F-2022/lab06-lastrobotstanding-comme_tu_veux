/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : SonnyRobot.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include <iostream>
#include <librobots.h>

#include "SonnyRobot.h"
#include "../action.h"

std::string SonnyRobot::action(std::vector<std::string> updates) {
    for (const std::string &update: updates) {
        std::vector<std::string> actionParameters = split(update, " ", 1);

        std::string action = actionParameters.at(0);

        switch (Action::resolveAction(action)) {
            case Action::Name::BOARD:
                std::cout << "BOARD" << std::endl;
                break;
            case Action::Name::DAMAGE:
                std::cout << "DAMAGE" << std::endl;
                break;
            case Action::Name::MOVE:
                std::cout << "MOVE" << std::endl;
                break;
            case Action::Name::ATTACK:
                std::cout << "ATTACK" << std::endl;
                break;
            case Action::Name::WAIT:
                std::cout << "WAIT" << std::endl;
                break;
            default:
                break;
        }
    }
    return "";

}

void SonnyRobot::setConfig(size_t width, size_t height, unsigned int energy, unsigned int power) {
    this->mapWidth = width;
    this->mapHeight = height;
    this->energy = energy;
    this->power = power;
}

std::string SonnyRobot::name() const {
    return this->ROBOT_NAME;
}
