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

class SonnyRobot {
    const std::string ROBOT_NAME = "Sonny";
public:
    size_t x = 0,y = 0;
    SonnyRobot(size_t width, size_t height, unsigned energy, unsigned power);

    void setCoords(size_t xCoord, size_t yCoord);

    std::string action(std::vector<std::string> updates);

    std::string name();

};

#endif //ROBOT_SONNYROBOT_H
