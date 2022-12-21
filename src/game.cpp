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
#include <iomanip>
#include <random>
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

        // Translate vector of entitiesState elements to string to display
        for (const auto &entity: entitiesState) {
            if(entity.disabled) {
                continue;
            }

            char entityChar;

            if (entity.type == State::Type::Robot) {
                entityChar = 'R';
            }

            if (entity.type == State::Type::Bonus) {
                entityChar = 'B';
            }

            grid.at((size_t)entity.coords.y).at((size_t)entity.coords.x) = entityChar;
        }

        // Display grid with libdio
        Display::saveCursorPosition();
        cout << Display::displayGrid<string>(grid, false);
        Display::restoreCursorPosition();


//        // Process each robot action
//        for (size_t index = 0; auto &robotState: robotsState) {
//            // If robot is dead, skip it
//            if (!robotState.getAliveState()) {
//                continue;
//            }
//
//            vector<string> actionParameters = split(robotState.robot->action({"board R               B      R "}), " ",
//                                                    2);
//
//            string action = actionParameters.at(0);
//            string parameters = actionParameters.at(1);
//
//            switch (Action::resolveAction(action)) {
//                case Action::Name::ATTACK:
//                    attackFlag = true;
//                    attack(Point::fromStrToPoint(parameters), robotState);
//                    break;
//                case Action::Name::MOVE:
//                    move(Point::fromStrToPoint(parameters), robotState);
//                    break;
//                case Action::Name::WAIT:
//                    break;
//                default:
//                    break;
//            }
//            ++index;
//        }

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
        entitiesState.push_back(
                RobotState(getNewId(),
                           new SonnyRobot(),
                           getFreeRandomPoint(),
                           DEFAULT_FIELDOFVIEW,
                           DEFAULT_ENERGY,
                           DEFAULT_POWER)
        );
    }
}


//string Game::damage(const Point coords, RobotState &attacker) {
//    string action;
//
//    Point attackerCoords = attacker.getCoords();
//
//    Point delta = attackerCoords + coords;
//
//    // Search robot to attack iterator
//    auto robot = find_if(this->robotsState.begin(), this->robotsState.end(),
//                         [&delta](RobotState r) {
//                             return r.getCoords() == delta;
//                         });
//
//    if (robot != this->robotsState.end()) {
//        // Add the information that he took damage from attacker
//
//        int dist = attacker.getCoords().distance(robot->getCoords());
//
//        unsigned attackPower = dist < 2 ? attacker.getPower() * 2 : dist < 3 ? attacker.getPower() : 0;
//
//        action = Action::generateDamage(attacker.getCoords(), attackPower);
//
//        robot->setEnergy(robot->getEnergy() - attackPower);
//
//        if (robot->getEnergy() <= 0) {
//            robot->die();
//        }
//        robot->addUpdate(action);
//    }
//
//    return action;
//}
//
//string Game::attack(const Point coords, RobotState &attacker) {
//    return Game::damage(coords, attacker);
//}
//
//bool Game::isRobotAt(Point coords) {
//    auto it = find_if_not(robotsState.begin(), robotsState.end(),
//                          [&coords](RobotState robotState) {
//                              return robotState == coords;
//                          });
//    return it != robotsState.end();
//}
//
//std::string Game::move(const Point direction, RobotState &robot) {
//    // check if the x value is between -1 and 1 and the y value is between -1 and 1 with ternary operator
//    Point newDirection = {direction.x <= -1 ? -1 : direction.x >= 1 ? 1 : direction.x,
//                          direction.y <= -1 ? -1 : direction.y >= 1 ? 1 : direction.y};
//
//    // Search robot to attack iterator
//    auto robotOnMap = find_if(this->robotsState.begin(), this->robotsState.end(),
//                              [&robot](RobotState r) {
//                                  return r.getCoords() == robot.getCoords();
//                              });
//    // TODO: check if there is multiple robot on the same position
//    Point::wrap(robot.getCoords() += newDirection, 0, SIZE_GRID);
//
//    return "move " + (string) newDirection;
//}

Point Game::getFreeRandomPoint() {
    uniform_int_distribution<int> rand(0, SIZE_GRID - 1);

    while (true) {
        Point p(rand(randomGenerator), rand(randomGenerator));

        if (!any_of(entitiesState.begin(), entitiesState.end(), [&p](auto &entity) { return entity.coords == p; })) {
            return p;
        }
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

        entitiesState.push_back(BonusState(getNewId(), getFreeRandomPoint(), type, rand_bonus_amount(randomGenerator)));
    }
}

size_t Game::getNewId() {
    auto it = max_element(entitiesState.begin(), entitiesState.end(),
                          [](auto &lhs, auto &rhs) {
                              return lhs.getId() < rhs.getId();
                          });

    return it != entitiesState.end() ? it->getId() + 1 : 0;
}







