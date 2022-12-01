/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : SonnyRobot.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_SONNYROBOT_H
#define ROBOT_SONNYROBOT_H

#include <cstdlib>
#include <string>
#include <vector>
#include <librobots.h>

class SonnyRobot : public Robot {
    enum Action {
        NOTDEFINED,
        BOARD,
        DAMAGE,
        MOVE,
        ATTACK,
        WAIT
    };

    const std::string ROBOT_NAME = "Sonny";

    size_t mapWidth = 0, mapHeight = 0;
    unsigned energy = 0, power = 0;

    static Action resolveAction(std::string &action);

    std::vector<std::vector<std::string>> internalMap;
public:
    void setConfig(size_t width, size_t height, unsigned energy, unsigned power) override;

    std::string action(std::vector<std::string> updates) override;

    [[nodiscard]] std::string name() const override;

};

#endif //ROBOT_SONNYROBOT_H
