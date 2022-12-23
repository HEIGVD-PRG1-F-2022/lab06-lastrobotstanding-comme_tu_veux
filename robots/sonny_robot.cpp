/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : sonny_robot.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include <librobots/Message.h>

#include "sonny_robot.h"
#include "robot_action_msg.h"

using namespace std;

void SonnyRobot::setConfig(size_t width, size_t height, unsigned int energy, unsigned int power) {
    this->mapWidth = width;
    this->mapHeight = height;
    this->energy = energy;
    this->power = power;
    this->map= vector(mapHeight, vector<string>(mapWidth, ""));
}

string SonnyRobot::action(vector<string> updates) {
    for (const string &update: updates) {
        vector<string> actionParameters = split(update, " ", 2);

        string action = actionParameters.at(0);
        string parameters;
        if (actionParameters.size() == 2) {
            parameters = actionParameters.at(1);
        }

        switch (RobotActionMsg::resolveAction(action)) {
            case RobotActionMsg::Name::BONUS:
                break;
            case RobotActionMsg::Name::Energy:
                this->energy += (unsigned) stoi(parameters);
                break;
            case RobotActionMsg::Name::Power:
                this->power += (unsigned) stoi(parameters);
                break;
            case RobotActionMsg::Name::BOARD:
                internalMap = fromStringToMap(parameters);
                break;
            case RobotActionMsg::Name::DAMAGE:
                vector<string> damageInfo = split(parameters, ",", 3);
                attacker = Point(damageInfo.at(0), damageInfo.at(1));
                energy -= (unsigned) stoi(damageInfo.at(2));
                break;
        }
    }

    target = targetToLock();
    target -= getCenterMap();

    ++counter;

    return actionType + " " + (string) target.normalize();
}

string SonnyRobot::name() const {
    return this->ROBOT_NAME;
}

Point SonnyRobot::targetToLock() {
    Point sonny = getCenterMap();
    Point shortestPoint(rand() % 5, rand() % 5);
    actionType = "move";

    for (size_t y = 0; y < internalMap.size(); ++y) {
        for (size_t x = 0; x < internalMap.at(y).size(); ++x) {
            string object = internalMap.at(y).at(x);
            if (!object.empty()) {
                Point current(x, y);
                if (sonny.distance(current) < sonny.distance(shortestPoint)) {
                    shortestPoint = current;
                    switch (object.at(0)) {
                        case 'R':
                            if (energy > 5 && counter > 50) {
                                actionType = "attack";
                            } else {
                                Point d = current.normalize();
                                d.x *= -1;
                                d.y *= -1;
                                shortestPoint = d;
                                actionType = "move";
                            }
                            break;
                    }
                }
            }
        }
    }
    return shortestPoint;
}

vector<vector<string>> SonnyRobot::fromStringToMap(const std::string map) {
    vector<vector<string>> mapVector;

    for (size_t y = 0; y < (size_t)FIELD_OF_VIEW; ++y) {
        vector<string> line;
        for (size_t x = 0; x < FIELD_OF_VIEW; ++x) {
            size_t offset = y * (size_t)FIELD_OF_VIEW;
            string car = map.substr(x + offset, 1);
            line.push_back(car == " " ? "" : car);
        }
        mapVector.push_back(line);
    }
    return mapVector;
}

Point SonnyRobot::getCenterMap() const {
    int x = int(mapWidth - 1) / 2;
    int y = int(mapHeight - 1) / 2;
    return {x, y};
}
