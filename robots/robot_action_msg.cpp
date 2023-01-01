/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : robot_action.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include "robot_action_msg.h"

using namespace std;

RobotActionMsg::Name RobotActionMsg::resolveAction(std::string &action) {
    if (action == BOARD_STRING)
        return RobotActionMsg::Name::BOARD;
    if (action == DAMAGE_STRING)
        return RobotActionMsg::Name::DAMAGE;
    if (action == POWER_STRING)
        return RobotActionMsg::Name::Power;
    if (action == ENERGY_STRING)
        return RobotActionMsg::Name::Energy;

    return RobotActionMsg::Name::NOTDEFINED;
}
