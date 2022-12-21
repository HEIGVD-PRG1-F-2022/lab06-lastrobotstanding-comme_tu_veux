/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : bonus_state.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 19.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_BONUS_STATE_H
#define ROBOT_BONUS_STATE_H

#include "../robots/point.h"
#include "state.h"

class BonusState : public State {
public:
    enum class Type {
        Energy,
        PowerUp
    };

    BonusState(size_t id, Point coords, Type bonusType, unsigned amount);

    unsigned getAmount();

private:
    unsigned amount;
    BonusState::Type bonusType;
};

#endif //ROBOT_BONUS_STATE_H
