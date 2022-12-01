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

std::string SonnyRobot::action(std::vector<std::string> updates) {
    for (const std::string& update: updates) {
        std::vector<std::string> actionParameter = split(update, " ", 1);

        std::string action = actionParameter.at(0);

        switch (resolveAction(action)) {
            case Action::BOARD:
                std::cout << "BOARD" << std::endl;
                break;
            case Action::DAMAGE:
                std::cout << "DAMAGE" << std::endl;
                break;
            case Action::MOVE:
                std::cout << "MOVE" << std::endl;
                break;
            case Action::ATTACK:
                std::cout << "ATTACK" << std::endl;
                break;
            case Action::WAIT:
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

SonnyRobot::Action SonnyRobot::resolveAction(std::string &action) {
    if (action == "board") return Action::BOARD;
    if (action == "damage") return Action::DAMAGE;
    if (action == "move") return Action::MOVE;
    if (action == "attack") return Action::ATTACK;
    if (action == "wait") return Action::WAIT;

    return SonnyRobot::NOTDEFINED;
}
