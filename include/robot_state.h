/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : robot_state.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 06.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_ROBOT_STATE_H
#define ROBOT_ROBOT_STATE_H

#include <vector>
#include <string>

#include "librobots/Robot.h"
#include "../robots/point.h"

class RobotState {
    size_t id;

    /**
     * Update to execute
     */
    std::vector<std::string> updates;

    /**
     * Update to execute on the next round
     */
    std::vector<std::string> nextUpdates;
public:
    Robot *robot;

    unsigned energy, power;

    /**
     * Initialize a new robot state
     * @param id
     * @param coords
     * @param robot
     * @param fieldOfView Size of the square visible by the robot
     * @param energy
     * @param power
     */
    RobotState(size_t id, Point coords, Robot *robot, size_t fieldOfView, unsigned int energy, unsigned int power);

    /**
     * State if the entity should be use or not
     */
    bool disable = false;

    /**
     * Get id set at the instantiation.
     * @return size_t id
     */
    size_t getId() const;

    /**
     * Coords of the state using Cartesian coordinate system (x,y)
     */
    Point coords;

    /**
     * Give a list of all update action the robot need to be done
     * @return
     */
    std::vector<std::string> getCurrentUpdate();

    /**
     * Push to the **NEXT** update list elements
     * @param update
     */
    void addUpdate(const std::string &update);

    void execUpdate();


};

#endif //ROBOT_ROBOT_STATE_H
