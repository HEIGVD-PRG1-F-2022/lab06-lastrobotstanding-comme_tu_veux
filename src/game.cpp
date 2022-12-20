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

const size_t NB_ROBOT = 2;
const size_t SIZE_GRID = NB_ROBOT * 10;

void Game::startGame() {
    robotsState.push_back(RobotState(new SonnyRobot(), Point(0, 0), 5, 10, 1));
    robotsState.push_back(RobotState(new SonnyRobot(), Point(6, 3), 5, 10, 1));

    vector<vector<string>> grid(SIZE_GRID, vector<string>(SIZE_GRID, " "));
    Display::init();
    time_t start, end;
    double time_taken;
    unsigned short counter = 0;

    while (true) {

        // Generate bonus every 20 turns
        if (counter == 20) {
            boni.push_back(generateBonus(getFreeRandomPoint(grid)));
            counter = 0;
        }

        end = clock();

        // Translate vector of RobotState elements and vector of Bonus elements to string to display
        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid.at(y).size(); ++x) {
                grid.at(y).at(x) = "";

                if (any_of(robotsState.begin(), robotsState.end(),
                           [&x, &y](RobotState r) { return r.coords == Point((int) x, (int) y); })) {
                    grid.at(y).at(x) = "R";
                }

                if (any_of(boni.begin(), boni.end(),
                           [&x, &y](Bonus b) { return b.getCoords() == Point((int) x, (int) y); })) {
                    grid.at(y).at(x) = "B";
                }
            }
        }

        // Calculate time taken by the program between each turn, debug only
        time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        Display::saveCursorPosition();
        cout << "Time taken by program is : " << fixed
             << time_taken << setprecision(5) << " sec" << endl;
        Display::restoreCursorPosition();
        start = clock();

        // Display grid with libdio
        Display::saveCursorPosition();
        cout << Display::displayGrid<string>(grid, false);
        Display::restoreCursorPosition();


        // Process each robot action
        for (size_t index = 0; auto &robotState: robotsState) {
            vector<string> actionParameters = split(robotState.robot->action(robotState.getUpdates()), " ", 2);

            string action = actionParameters.at(0);
            string parameters = actionParameters.at(1);

            switch (Action::resolveAction(action)) {
                case Action::Name::ATTACK:
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
            ++index;
        }
        //this_thread::sleep_for(chrono::seconds(1));
        ++counter;
    }
}

string Game::damage(const Point coords, RobotState &attacker) {
    string action;

    // Search robot to attack iterator
    auto robot = find_if(this->robotsState.begin(), this->robotsState.end(),
                         [&coords](RobotState r) {
                             return r.coords.x == coords.x && r.coords.y == coords.y;
                         });

    if (robot != this->robotsState.end()) {
        // Add the information that he took damage from attacker
        action = Action::generateDamage(attacker.coords, attacker.getPower());
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

std::string Game::move(const Point direction, RobotState &robot) {
    // check if the x value is between -1 and 1 and the y value is between -1 and 1 with ternary operator
    Point newDirection = {direction.x <= -1 ? -1 : direction.x >= 1 ? 1 : direction.x,
                          direction.y <= -1 ? -1 : direction.y >= 1 ? 1 : direction.y};

    // Search robot to attack iterator
    auto robotOnMap = find_if(this->robotsState.begin(), this->robotsState.end(),
                              [&robot](RobotState r) {
                                  return r.coords.x == robot.coords.x &&
                                         r.coords.y == robot.coords.y;
                              });
    // TODO: check if there is multiple robot on the same position
    Point::wrap(robot.coords += newDirection, 0, SIZE_GRID);

    return "move " + (string) newDirection;
}

Point Game::getFreeRandomPoint(const vector<vector<string>> &grid) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, (int)grid.size()-1);

    while (true) {
        Point point(distribution(generator), distribution(generator));
        if (grid.at((size_t) point.y).at((size_t) point.x) == "") {
            return point;
        }
    }

}

Bonus Game::generateBonus(const Point coords) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution_bonus_type(0, 1);

    auto type = (Bonus::Type) distribution_bonus_type(generator);

    unsigned max_value = 0;

    switch (type) {
        case Bonus::Type::Energy:
            max_value = 10;
            break;
        case Bonus::Type::PowerUp:
            max_value = 3;
            break;
    }

    uniform_int_distribution<unsigned> distribution_amount(1, max_value);

    return {coords, type, distribution_amount(generator)};
}
