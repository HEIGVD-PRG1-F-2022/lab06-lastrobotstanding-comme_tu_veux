/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : game.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/
#include <thread>
#include <chrono>
#include <librobots/Message.h>

#include "game.h"
#include "action.h"
#include "robots/sonny_robot.h"
#include "robot_state.h"

using namespace std;

void Game::startGame() {
    robotsState.push_back(RobotState(new SonnyRobot(), Point(0, 0), 5, 10, 1));
    robotsState.push_back(RobotState(new SonnyRobot(), Point(6, 3), 5, 10, 1));

    while (true) {
        for (size_t index = 0; auto &robotState: robotsState) {
            // vector<string> actionParameters = split(robotState.action(this->updates.at(index)), " ", 1);
            vector<string> actionParameters = split("attack 6,3", " ", 2);

            string action = actionParameters.at(0);
            string parameters = actionParameters.at(1);

            switch (Action::resolveAction(action)) {
                case Action::Name::ATTACK:
                    attack(Point::fromStrToPoint(parameters), robotState);
                    break;
                case Action::Name::DAMAGE:
                    break;
                case Action::Name::MOVE:
                    break;
                case Action::Name::WAIT:
                    break;
                default:
                    break;
            }
            ++index;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

string Game::damage(const Point coords, RobotState &attacker) {
    string action;

    // Search robot to attack iterator
    auto robot = find_if(this->robotsState.begin(), this->robotsState.end(),
                         [&coords](RobotState r) {
                             return r.getCoords().x == coords.x && r.getCoords().y == coords.y;
                         });

    if (robot != this->robotsState.end()) {
        // Add the information that he took damage from attacker
        action = Action::generateDamage(attacker.getCoords(), attacker.getPower());
        robot->addUpdate(action);
    }

    return action;
}

string Game::attack(const Point coords, RobotState &attacker) {
    return Game::damage(coords, attacker);
}

bool Game::isRobotAt(Point coords) {
    auto it = find_if_not(robotsState.begin(), robotsState.end(),
                          [&coords](RobotState robotState) {
                              return robotState == coords;
                          });
    return it != robotsState.end();
}
