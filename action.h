/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : action.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/
#ifndef ROBOT_ACTION_H
#define ROBOT_ACTION_H

#include <string>

class Action {
public:
    enum Name {
        NOTDEFINED,
        BOARD,
        DAMAGE,
        MOVE,
        ATTACK,
        WAIT
    };

    static Name resolveAction(std::string &action);
};

#endif //ROBOT_ACTION_H
