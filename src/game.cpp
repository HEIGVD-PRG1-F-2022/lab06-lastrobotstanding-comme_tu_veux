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
#include <libdio/display.h>
#include "librobots/Message.h"

#include "../include/game.h"
#include "../robots/action.h"
#include "../robots/sonny_robot.h"

using namespace std;

Game::Game() {
    Display::init();
    this->setupGame();
    randomGenerator.seed(r());
}

void Game::setupGame() {
    this->grid = Map(SIZE_GRID, vector<string>(SIZE_GRID));

    generateRobots(Game::NB_ROBOT);
}

void Game::startGame() {

    bool attackFlag = false;

    while (true) {
        // Generate bonus every 20 turns
        if (!(roundCount % 20) && roundCount != 0) {
            generateBoni(1);
        }

        display();

        for (RobotState &robotState: robotsState) {
            // skip robotState if dead
            if (robotState.disable) {
                continue;
            }

            vector<string> actionParameters = split(robotState.robot->action({getRobotView(robotState.coords)}), " ", 2);

            string action = actionParameters.at(0);
            string parameters = actionParameters.at(1);

            switch (Action::resolveAction(action)) {
                case Action::Name::ATTACK:
                    attackFlag = true;
                    attack(Point::fromStrToPoint(parameters), robotState);
                    break;
                case Action::Name::MOVE:
                    move(Point::fromStrToPoint(parameters), robotState);
                    break;
                case Action::Name::WAIT:
                    break;
                default:
                    break;
            }
        }

        // Check if there was an attack in the last 100 turns if not end the game
        if (roundCount > 100) {
            if (!attackFlag) {
                return;
            } else {
                attackFlag = false;
            }
            roundCount = 1;
        }

        this_thread::sleep_for(chrono::milliseconds(20));
        ++roundCount;
    }
}

void Game::generateRobots(unsigned nbRobots) {
    for (unsigned i = 0; i < nbRobots; i++) {
        robotsState.emplace_back(
                getUniqueRobotId(),
                getFreeRandomPoint(),
                new SonnyRobot(),
                DEFAULT_FIELDOFVIEW,
                DEFAULT_ENERGY,
                DEFAULT_POWER
        );
    }
}


string Game::damage(const Point coords, RobotState &attacker) {
    string action;

    Point attackerCoords = attacker.coords;

    Point delta = attackerCoords + coords;

    // Search robot to attack iterator
    auto robot = find_if(this->robotsState.begin(), this->robotsState.end(),
                         [&delta](RobotState r) {
                             return r.coords == delta;
                         });

    if (robot != this->robotsState.end()) {
        // Add the information that he took damage from attacker

        int dist = attacker.coords.distance(robot->coords);

        unsigned attackPower = dist < 2 ? attacker.getPower() * 2 : dist < 3 ? attacker.getPower() : 0;

        action = Action::generateDamage(attacker.coords, attackPower);

        robot->setEnergy(robot->getEnergy() - attackPower);

        if (robot->getEnergy() <= 0) {
            robot->disable = true;
        }
        robot->addUpdate(action);
    }

    return action;
}

string Game::attack(const Point coords, RobotState &attacker) {
    return Game::damage(coords, attacker);
}

std::string Game::move(Point direction, RobotState &robot) {
    // Search robot to attack iterator
    auto robotOnMap = find_if(this->robotsState.begin(), this->robotsState.end(),
                              [&robot](RobotState r) {
                                  return r.coords == robot.coords;
                              });

    // TODO: check if there is multiple robot on the same position

    robot.coords += direction.normalize();

    Point::wrap(robot.coords, 0, SIZE_GRID - 1);

    return "move " + (string) direction.normalize();
}

Point Game::getFreeRandomPoint() {
    uniform_int_distribution<int> rand(0, SIZE_GRID - 1);

    while (true) {
        Point p(rand(randomGenerator), rand(randomGenerator));

        if (any_of(robotsState.begin(), robotsState.end(), [&p](RobotState &r) { return r.coords == p; })) {
            continue;
        }

        if (any_of(boniState.begin(), boniState.end(), [&p](BonusState &b) { return b.coords == p; })) {
            continue;
        }

        return p;
    }
}

void Game::generateBoni(unsigned nbBoni) {
    uniform_int_distribution<int> rand_bonus_type(0, 1);
    unsigned max_value = 0;

    for (unsigned i = 0; i < nbBoni; i++) {
        auto type = (BonusState::Type) rand_bonus_type(randomGenerator);

        switch (type) {
            case BonusState::Type::Energy:
                max_value = 10;
                break;
            case BonusState::Type::PowerUp:
                max_value = 3;
                break;
        }

        uniform_int_distribution<unsigned> rand_bonus_amount(1, max_value);

        boniState.emplace_back(getFreeRandomPoint(), type, rand_bonus_amount(randomGenerator));
    }
}

size_t Game::getUniqueRobotId() {
    auto it = max_element(robotsState.begin(), robotsState.end(),
                          [](auto &lhs, auto &rhs) {
                              return lhs.getId() < rhs.getId();
                          });

    return it != robotsState.end() ? it->getId() + 1 : 0;
}


void Game::display() {
    for(auto &y : grid){
        for(auto &x : y) {
            x = "";
        }
    }

    for (const auto &robot: robotsState) {
        if (robot.disable) {
            continue;
        }
        grid.at((size_t) robot.coords.y).at((size_t) robot.coords.x) = "R";
    }

    for (const auto &bonus: boniState) {
        if (bonus.disable) {
            continue;
        }
        grid.at((size_t) bonus.coords.y).at((size_t) bonus.coords.x) = "B";
    }

    // Display grid with libdio
    Display::saveCursorPosition();
    cout << Display::displayGrid<string>(grid, false);
    Display::restoreCursorPosition();
}

std::string Game::getRobotView(Point coords) {
    int topLeft = int(DEFAULT_FIELDOFVIEW -1 / 2);
    coords -= Point(topLeft,topLeft);

    string map;

    for(size_t y = 0; y < DEFAULT_FIELDOFVIEW; ++y){
        for(size_t x = 0; x < DEFAULT_FIELDOFVIEW; ++x) {
            Point s = coords + Point(x,y);
            Point::wrap(s, 0, SIZE_GRID -1);

            map.push_back((grid.at((size_t)s.y).at((size_t)s.x).empty() ? ' ' : grid.at((size_t)s.y).at((size_t)s.x).at(0)));
        }
    }


    return "board " + map;
}






