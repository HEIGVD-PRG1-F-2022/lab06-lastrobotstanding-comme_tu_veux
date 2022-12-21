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
#include <chrono>
#include <random>

#include "librobots/Robot.h"
#include "robot_state.h"
#include "../robots/point.h"
#include "bonus_state.h"
#include "state.h"

class Game {
    static const size_t NB_ROBOT = 2;
    static const size_t SIZE_GRID = NB_ROBOT * 10;

    const unsigned DEFAULT_ENERGY = 10;
    const unsigned DEFAULT_POWER = 1;
    const unsigned DEFAULT_FIELDOFVIEW = 5;

    typedef std::vector<std::vector<std::string>> Map;

    std::random_device r;
    std::default_random_engine randomGenerator;

    Map grid;
    std::vector<State> entitiesState;

    size_t roundCount = 0;

public:
    Game();

    void setupGame();

    void startGame();

    /**
     * Generate a random free Point, it check if position is not already take by another entity
     * @return Point
     */
    Point getFreeRandomPoint();

    /**
     * Generate a new unique id to use for an entity
     * @return
     */
    size_t getNewId();


    /**
     * Generate and add robot entities into the state manager
     * @param nbRobots
     */
    void generateRobots(unsigned nbRobots);

    /**
     * Generate and add bonus entities into the state manager
     * @param nbBoni
     */
    void generateBoni(unsigned nbBoni);

    std::string attack(Point coords, RobotState &attacker);

    std::string damage(Point coords, RobotState &attacker);

    std::string move(Point coords, RobotState &robot);





    bool isRobotAt(Point coords);
};

#endif // ROBOT_GAME_H
