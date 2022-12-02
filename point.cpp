//
// Created by Syra on 02.12.2022.
//

#include "point.h"
#include <librobots.h>
#include <sstream>

Point Point::fromStrToPoint(std::string coords, std::string sep) {
    std::vector<std::string> points = split(coords, ",", 1);

    size_t x, y;
    std::stringstream xCoord(points.at(0));
    xCoord >> x;
    std::stringstream yCoord(points.at(1));
    yCoord >> y;

    return Point(x, y);
}
