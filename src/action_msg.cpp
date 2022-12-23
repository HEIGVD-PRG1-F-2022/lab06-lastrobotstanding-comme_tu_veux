/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : action_msg.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/
#include <bits/stdc++.h>

#include "../include/action_msg.h"

using namespace std;

ActionMsg::Name ActionMsg::resolveAction(std::string &action) {
    if (action == BOARD_STRING)
        return ActionMsg::Name::BOARD;
    if (action == DAMAGE_STRING)
        return ActionMsg::Name::DAMAGE;
    if (action == MOVE_STRING)
        return ActionMsg::Name::MOVE;
    if (action == ATTACK_STRING)
        return ActionMsg::Name::ATTACK;
    if (action == WAIT_STRING)
        return ActionMsg::Name::WAIT;
    if (action == POWER_STRING)
        return ActionMsg::Name::Power;
    if (action == ENERGY_STRING)
        return ActionMsg::Name::Energy;

    return ActionMsg::Name::NOTDEFINED;
}

std::string ActionMsg::generateDamage(Point coords, unsigned int energy) {
    return DAMAGE_STRING + " " + (std::string) coords + "," + std::to_string(energy);
}

std::vector<std::string> ActionMsg::split(std::string str, char delimiter) {
    // Using str in a string stream
    stringstream ss(str);
    vector<string> res;
    string token;
    while (getline(ss, token, delimiter)) {
        res.push_back(token);
    }
    return res;
}