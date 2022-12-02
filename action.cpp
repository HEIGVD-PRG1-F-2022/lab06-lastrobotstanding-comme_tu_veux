/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : action.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include "action.h"

Action::Name Action::resolveAction(std::string &action) {
    if (action == "board") return Action::Name::BOARD;
    if (action == "damage") return Action::Name::DAMAGE;
    if (action == "move") return Action::Name::MOVE;
    if (action == "attack") return Action::Name::ATTACK;
    if (action == "wait") return Action::Name::WAIT;

    return Action::Name::NOTDEFINED;
}
