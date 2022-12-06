//
// Created by Syra on 02.12.2022.
//

#include "point.h"
#include "librobots/Message.h"
#include <librobots/Robot.h>
#include <sstream>

using namespace std;

Point Point::fromStrToPoint(string coords, string sep) {
    vector<std::string> points = split(coords, ",", 1);

    size_t x, y;
    stringstream xCoord(points.at(0));
    xCoord >> x;
    stringstream yCoord(points.at(1));
    yCoord >> y;

    return Point(x, y);
}
