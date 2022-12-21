/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : state.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 21.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/


#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include <cstddef>

#include "../robots/point.h"

class State {
protected:
    size_t id;

public:
    enum Type {
        Robot,
        Bonus
    };

    explicit State(size_t id) : id(id) {};

    /**
     * State if the state should be use or not
     */
    bool disabled = false;

    /**
     * Type of entity state
     */
    Type type;

    /**
     * Get id set at the instantiation.
     * @return size_t id
     */
    size_t getId();

    /**
     * Coords of the state using Cartesian coordinate system (x,y)
     */
    Point coords;

};

#endif //ROBOT_STATE_H
