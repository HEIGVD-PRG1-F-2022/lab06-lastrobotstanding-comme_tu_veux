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

#include "point.h"

#include <vector>
#include <librobots.h>

class Game {
    //vectors (energy/power/position/robots)
    //vector board (25,'-')
    //  while true
    //      for each (auto& robots)
    //      1. read answer from robots
    //      2. update board (actions)
    //      3. appel action function (ask robots actions)

    std::vector<unsigned> energyGlobalState;
    std::vector<unsigned> powerGlobalState;
    std::vector<Point> positionGlobalState;
    std::vector<Robot*> robotsGlobalState;

    std::vector<std::vector<std::string>> updates;
public:
    void startGame();
    std::string attack(Point coords);
    bool isRobotAt(Point coords);
    std::iter_difference_t<size_t> getRobotIndex(Point coords);
};


#endif //ROBOT_GAME_H
