//
// Project name : LAB 05 - Refactor
// Project members :
// - Florian Duruz
// - Aellen Quentin
//

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
