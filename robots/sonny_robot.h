/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : sonny_robot.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_SONNY_ROBOT_H
#define ROBOT_SONNY_ROBOT_H

#include <cstdlib>
#include <string>
#include <vector>
#include <librobots/Robot.h>
#include "./point.h"

class SonnyRobot : public Robot {

    const std::string ROBOT_NAME = "Sonny";

    const int FIELD_OF_VIEW = 5;

    size_t mapWidth = 0, mapHeight = 0;
    unsigned energy = 0, power = 0;
    unsigned counter = 0;

    std::string actionType;

    Point target;
    Point targetToLock();

    Point attacker;

    [[nodiscard]] Point getCenterMap() const;

    /**
     * Internal view of the robot for it's proxmity mapping
     */
    std::vector<std::vector<std::string>> internalMap;

    /**
     * Real size 2D array to store boni
     */
    std::vector<std::vector<std::string>> map;

    /**
     * Convert string to a 2D array exploitable map
     * @param map
     * @return
     */
    std::vector<std::vector<std::string>> fromStringToMap(std::string map);



public:
    void setConfig(size_t width, size_t height, unsigned energy, unsigned power) override;

    std::string action(std::vector<std::string> updates) override;

    [[nodiscard]] std::string name() const override;

};

#endif //ROBOT_SONNY_ROBOT_H
