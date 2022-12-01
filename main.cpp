//
// Project name : LAB 06 - Robot
// Project members :
// - Atasever Mehmet
// - Salamin Chloé
// - Aellen Quentin
//

#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <iostream>
#include "robots/SonnyRobot.h"
#include "libdio/display.h"
#include <librobots.h>

#define Map vector<vector<string>>

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

    Map grid(GRID_SIZE, vector<string>(GRID_SIZE, " "));

    vector<Robot*> robots(ROBOT_NUMBER, new SonnyRobot());

    vector<string> updates;

    updates.push_back("attack R                B      R");

    robots.at(0)->action(updates);

    this_thread::sleep_for(10s);

    return EXIT_SUCCESS;
}
