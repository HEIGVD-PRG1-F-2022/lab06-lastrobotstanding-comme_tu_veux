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

#include "../robots/point.h"

#include "robot_state.h"
#include "bonus_state.h"





class Game {
    static const size_t NB_ROBOT = 8;
    static const size_t SIZE_GRID = 20;

    const unsigned DEFAULT_ENERGY = 10;
    const unsigned DEFAULT_POWER = 1;
    const unsigned DEFAULT_FIELDOFVIEW = 5;

    typedef std::vector<std::vector<std::string>> Map;

    std::random_device r;
    std::default_random_engine randomGenerator;

    Map grid;

    std::vector<RobotState> robotsState;
    std::vector<BonusState> boniState;

    size_t roundCount = 0;

public:
    Game();

    /**
     * Initialize the grid and the starting number of robots
     */
    void setupGame();

    /**
     * Start the main game loop
     */
    void startGame();

    /**
     * Display game board with all entities
     */
    void display();

    /**
     * Generate a random free Point, it check if position is not already take by another entity
     * @return Point
     */
    Point getFreeRandomPoint();

    /**
     * Generate a new unique id to use for an entity
     * @return
     */
    size_t getUniqueRobotId();

    /**
     *
     * @param coords
     * @return
     */
    std::string getRobotBoard(Point coords);

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

    /**
     * Search for a robot at a coords, by default it will check if it's alive
     * @param r vector<RobotState> list all robot states
     * @param coords x,y point to check
     * @param alive if you want it alive or not, be default it's alive
     * @return iterator of the founded robot, if not it will be the last iteration of the vector
     */
    std::vector<RobotState>::iterator searchRobot(std::vector<RobotState> &r, Point coords, bool alive = true);

    /**
     * Search for a robot at a coords, by default it will check if it's alive
     * @param r vector<RobotState> list of all robot states
     * @param coords x,y point to check
     * @param id size_t id to ignore of the robot to search
     * @param alive if you want it alive or not, be default it's alive
     * @return iterator of the founded robot, if not it will be the last iteration of the vector
     */
    std::vector<RobotState>::iterator searchRobot(std::vector<RobotState> &r, Point coords, size_t id, bool alive = true);

    /**
     * Search for a bonus at a coords, by default it will check if it's enable on the board
     * @param b vector<BonusState> list of all bonus
     * @param coords x,y point to check
     * @param enable if the bonus is active on the board
     * @return iterator of the founded bonus, if not it will be the last iteration of the vector
     */
    std::vector<BonusState>::iterator searchBonus(std::vector<BonusState> &b, Point coords, bool enable = true);

    /**
     * Generate an attack string and update state of the robot
     * @param coords
     * @param attacker
     * @return
     */
    std::string attack(Point coords, RobotState &attacker);

    /**
     * Search robot on coords, generate damage taken by the attacker and update state of the robot
     * @param coords
     * @param attacker
     * @return
     */
    std::string damage(Point coords, RobotState &attacker);

    /**
     * Generate moving string and update state of the robot
     * @param coords
     * @param robot
     * @return
     */
    std::string move(Point coords, RobotState &robot);
};

#endif // ROBOT_GAME_H
