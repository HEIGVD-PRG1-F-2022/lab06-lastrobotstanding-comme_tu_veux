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

class BonusState {
public:
    /**
     * Type of bonus
     */
    enum class Type {
        Energy,
        PowerUp
    };

    /**
     * Initialize a new BonusState
     * @param coords
     * @param bonusType
     * @param amount
     */
    BonusState(Point coords, Type bonusType, unsigned amount);

    /**
     * State if the entity should be use or not
     */
    bool disable = false;

    /**
     * Coords of the state using Cartesian coordinate system (x,y)
     */
    Point coords;

    /**
     * Value of the bonus
     * @return unsigned amount
     */
    unsigned getAmount();

    /**
     * Get the type of bonus
     * @return enum Type
     */
    Type getType();

private:
    unsigned amount;
    BonusState::Type bonusType;
};

#endif //ROBOT_BONUS_STATE_H
