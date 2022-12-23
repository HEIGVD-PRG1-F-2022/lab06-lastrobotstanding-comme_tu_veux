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
    generateBoni(120);
}

void Game::startGame() {

    bool attackFlag = false;

    for (RobotState &robotState: robotsState) {
        robotState.addUpdate(getRobotView(robotState.coords));
    }

    while (true) {
        // Generate bonus every 20 turns
        if (!(roundCount % 20) && roundCount != 0) {
            generateBoni(20);
        }

        display();

        for (RobotState &robotState: robotsState) {
            // skip robotState if dead
            if (robotState.disable) {
                continue;
            }
            string todo = robotState.robot->action(robotState.getCurrentUpdate());
            vector<string> actionParameters = split(todo, " ", 2);

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

        getRobotsView(this->robotsState);

        for (RobotState &robotState: this->robotsState) {
            robotState.execUpdate();
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
                                  return r.coords == robot.coords && robot.getId() != r.getId() && !robot.disable;
                              });

    // Kill robot with lower energy if on the same spot
    if (robotOnMap != robotsState.end()) {
        if (robot.getEnergy() < robotOnMap->getEnergy()) {
            robot.disable = true;
        } else {
            robotOnMap->disable = true;
        }
    }

    // Check if bonus on the map
    auto bonus = find_if(this->boniState.begin(), this->boniState.end(), [&robot](BonusState bonusState) {
        return robot.coords == bonusState.coords && !bonusState.disable;
    });

    if (bonus != boniState.end()) {
        switch (bonus->getType()) {
            case BonusState::Type::Energy:
                robot.energy += bonus->getAmount();
                robot.addUpdate("energy " + to_string(bonus->getAmount()));
                break;
            case BonusState::Type::PowerUp:
                robot.power += bonus->getAmount();
                robot.addUpdate("power " + to_string(bonus->getAmount()));
                break;
        }

        bonus->disable = true;
    }

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

    for (const auto &bonus: boniState) {
        if (bonus.disable) {
            continue;
        }
        grid.at((size_t) bonus.coords.y).at((size_t) bonus.coords.x) = "B";
    }

    for (const auto &robot: robotsState) {
        if (robot.disable) {
            continue;
        }
        grid.at((size_t) robot.coords.y).at((size_t) robot.coords.x) = "R";
    }

    // Display grid with libdio
    Display::saveCursorPosition();
    cout << Display::displayGrid<string>(grid, false);

    Display::DString d;

    d << "\n";

    for (RobotState robotState: robotsState) {
        d << to_string(robotState.getId())
          << " - "
          << robotState.robot->name()
          << " Energy : "
          << robotState.getEnergy()
          << " Power : "
          << robotState.getPower()
          << " : "
          << (!robotState.getCurrentUpdate().empty() ? robotState.getCurrentUpdate().back() : "")
          << "\n";
    }
    d.print();

    Display::restoreCursorPosition();
}

std::string Game::getRobotView(Point coords) {
    size_t offset = int(DEFAULT_FIELDOFVIEW - 1 / 2);

    string map;

    for (size_t y = 0; y < DEFAULT_FIELDOFVIEW; ++y) {
        for (size_t x = 0; x < DEFAULT_FIELDOFVIEW; ++x) {
            Point s = coords + Point(x - offset, y - offset);
            Point::wrap(s, 0, SIZE_GRID - 1);

            auto robot = find_if(robotsState.begin(), robotsState.end(), [&s](RobotState &r) { return r.coords == s && !r.disable; });
            auto bonus = find_if(boniState.begin(), boniState.end(), [&s](BonusState &b) { return b.coords == s && !b.disable; });

            string entity = " ";

            if (robot != robotsState.end()) {
                entity = 'R';
            }

            if (bonus != boniState.end()) {
                entity = 'B';
            }

            map += entity;
        }
    }


    return "board " + map;
}

void Game::getRobotsView(vector<RobotState> &r) {
    for (RobotState robotState: r) {
        robotState.addUpdate(getRobotView(robotState.coords));
    }
}






