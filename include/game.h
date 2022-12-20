/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : game.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_GAME_H
#define ROBOT_GAME_H

#include <vector>
#include "librobots/Robot.h"
#include "robot_state.h"
#include "point.h"
#include "bonus.h"

class Game {
    std::vector<RobotState> robotsState;
    std::vector<Bonus> boni;
public:
    void startGame();

    std::string attack(const Point coords, RobotState &attacker);

    std::string damage(const Point coords, RobotState &attacker);

    std::string move(const Point coords, RobotState &robot);

    Point getFreeRandomPoint(const std::vector<RobotState> &robotState, const std::vector<Bonus> &boni);

    Bonus generateBonus(const Point coords);

    bool isRobotAt(Point coords);

};


#endif //ROBOT_GAME_H
