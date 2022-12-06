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
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

#include "game.h"
#include "action.h"
#include "robots/sonny_robot.h"

using namespace std;

void Game::startGame() {
    positionGlobalState.push_back(Point(2, 3));
    robotsGlobalState.push_back(new sonny_robot());

    while (true) {
        for (size_t index = 0; auto &robot: robotsGlobalState) {
            //vector<string> actionParameters = split(robot.action(this->updates.at(index)), " ", 1);
            vector<string> actionParameters = split("attack 6,3", " ", 1);

            string action = actionParameters.at(0);
            string parameters = actionParameters.at(1);

            switch (Action::resolveAction(action)) {
                case Action::Name::ATTACK:
                    attack(Point::fromStrToPoint(parameters));
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

string Game::attack(Point coords) {
    size_t index = getRobotIndex(coords);
    cout << (string)coords << " name: " << robotsGlobalState.at(index)->name() << endl;
    return "Ouille, j'ai mal";
}

iter_difference_t<size_t> Game::getRobotIndex(Point coords) {
    auto itr = find_if(this->positionGlobalState.begin(), this->positionGlobalState.end(),
                            [&coords](Point p) { return p.x == coords.x && p.y == coords.y; });

    return distance(this->positionGlobalState.begin(), itr) - 1;
}

bool Game::isRobotAt(Point coords) {
    return false;
}
