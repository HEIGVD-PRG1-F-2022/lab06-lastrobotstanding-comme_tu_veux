/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : sonny_robot.cpp
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
#include <librobots/Message.h>

#include "sonny_robot.h"
#include "../include/action.h"

using namespace std;

string SonnyRobot::action(vector<string> updates) {
    for (const string &update: updates) {
        vector<string> actionParameters = split(update, " ", 2);

        string action = actionParameters.at(0);

        switch (Action::resolveAction(action)) {
            case Action::Name::BOARD:
                cout << "BOARD" << endl;
                break;
            case Action::Name::DAMAGE:
                cout << "DAMAGE" << endl;
                break;
            case Action::Name::MOVE:
                cout << "MOVE" << endl;
                break;
            case Action::Name::ATTACK:
                cout << "ATTACK" << endl;
                break;
            case Action::Name::WAIT:
                cout << "WAIT" << endl;
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

string SonnyRobot::name() const {
    return this->ROBOT_NAME;
}
