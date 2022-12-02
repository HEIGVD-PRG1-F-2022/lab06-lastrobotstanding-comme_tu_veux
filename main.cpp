/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : main.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 29.11.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <iostream>
#include "robots/SonnyRobot.h"
#include "libdio/display.h"
#include "game.h"
#include <librobots.h>

using namespace std;

const int ROBOT_NUMBER = 20;
const int GRID_SIZE = 10 * ROBOT_NUMBER;

// TODO: use action to transmit robot possition
/*
 * void setupRobotOnGrid(vector<SonnyRobot> &robots) {
    srand(time(NULL));

    bool freeCoords = true;

    for (auto &robot: robots) {
        while (freeCoords) {
            size_t x = (size_t) rand() % GRID_SIZE;
            size_t y = (size_t) rand() % GRID_SIZE;

            freeCoords = !any_of(
                    robots.begin(),
                    robots.end(),
                    [x, y](SonnyRobot &robot) {
                        return robot.x == x && robot.y == y;
                    });

            if (freeCoords) {
                robot.setCoords(x, y);
                freeCoords = false;
            }
        }
        freeCoords = true;
    }
}
 */

int main() {

    Game mainGame;

    mainGame.startGame();

    return EXIT_SUCCESS;
}
