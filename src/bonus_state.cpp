/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : bonus_state.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 19.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include "../include/bonus_state.h"

BonusState::BonusState(Point coords, Type bonusType, unsigned amount) {
    this->coords = coords;
    this->bonusType = bonusType;
    this->amount = amount;
}

unsigned BonusState::getAmount() {
    return this->amount;
}