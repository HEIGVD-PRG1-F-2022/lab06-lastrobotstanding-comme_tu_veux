/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : action_msg.h
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
#define ROBOT_ACTION_MSG_H

#include <string>
#include <vector>
#include "../robots/point.h"

const std::string BOARD_STRING = "board",
        DAMAGE_STRING = "damage",
        MOVE_STRING = "move",
        ATTACK_STRING = "attack",
        WAIT_STRING = "wait",
        POWER_STRING = "power",
        ENERGY_STRING = "energy";

class ActionMsg {
public:
    /**
     * List of each available action
     */
    enum Name {
        NOTDEFINED,
        BOARD,
        DAMAGE,
        MOVE,
        ATTACK,
        WAIT,
        BONUS,
        Energy,
        Power,
    };

    /**
     * Convert the message action string to it's corresponding enumeration if there is one available for the message
     * @param action message of the wanted action
     * @return enumeration of the corresponding action
     */
    static Name resolveAction(std::string &action);

    /**
     * Generate string message for damage
     * @param coords from where the damage come from
     * @param energy amount of energy of the damage
     * @return string with coords and the amount of energy to remove
     */
    static std::string generateDamage(Point coords, unsigned int energy);

    /**
     * Split one string into a vector<string> by specified delimiter, default delimiter is space
     * src : https://www.geeksforgeeks.org/cpp-string-to-vector-using-delimiter/
     * @param str
     * @param delimiter
     * @return
     */
    static std::vector<std::string> split(std::string str, char delimiter = ' ');
};

#endif //ROBOT_ACTION_MSG_H
