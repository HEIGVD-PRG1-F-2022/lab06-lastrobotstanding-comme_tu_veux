//
// Project name : LAB 06 - Robot
// Project members :
// - Atasever Mehmet
// - Salamin Chloé
// - Aellen Quentin
//

#include "SonnyRobot.h"

std::string SonnyRobot::name() {
    return this->ROBOT_NAME;
}

SonnyRobot::SonnyRobot(size_t width, size_t height, unsigned int energy, unsigned int power) {

}

std::string SonnyRobot::action(std::vector<std::string> updates) {
    return std::string();
}

void SonnyRobot::setCoords(size_t xCoord, size_t yCoord) {
    this->x = xCoord;
    this->y = yCoord;
}
