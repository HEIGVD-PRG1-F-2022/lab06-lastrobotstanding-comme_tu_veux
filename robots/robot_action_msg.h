/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : robot_action.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/
#ifndef ROBOT_ACTION_MSG_H
#define ROBOT_ACTION_H

#include <string>
#include "point.h"

const std::string BOARD_STRING = "board";
const std::string DAMAGE_STRING = "damage";
const std::string MOVE_STRING = "move";
const std::string ATTACK_STRING = "attack";
const std::string WAIT_STRING = "wait";
const std::string POWER_STRING = "power";
const std::string ENERGY_STRING = "energy";

class RobotActionMsg {
public:
    enum Name {
        NOTDEFINED,
        BOARD,
        DAMAGE,
        BONUS,
        Energy,
        Power,
    };

    /**
     * Convert string of a specified action to it's corresponding enum
     * @param action string to convert
     * @return the specific enum of the action
     */
    static Name resolveAction(std::string &action);
};

#endif //ROBOT_ACTION_MSG_H
