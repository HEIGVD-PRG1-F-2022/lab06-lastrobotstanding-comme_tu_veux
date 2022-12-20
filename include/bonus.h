/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : bonus.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 19.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_BONUS_H
#define ROBOT_BONUS_H

#include "point.h"

class Bonus {
public:
    enum Type {
        Energy,
        PowerUp
    };
    Bonus(Type bonusType, unsigned amount) : amount(amount), bonusType(bonusType) {};

    unsigned getAmount();

    Point getCoords();
private:
    Point coords;
    unsigned amount;
    Bonus::Type bonusType;
};

#endif //ROBOT_BONUS_H
