/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : Point.cpp
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include "point.h"
#include "librobots/Message.h"
#include <vector>
#include <sstream>

using namespace std;

Point Point::fromStrToPoint(const string &coords, const string &sep) {
    vector<string> points = split(coords, ",", 2);

    size_t x, y;
    stringstream xCoord(points.at(0));
    xCoord >> x;
    stringstream yCoord(points.at(1));
    yCoord >> y;

    //return a new Point object without segmentation fault
    return {x, y};
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::operator string() const {
    return to_string(x) + "," + to_string(y);
}

bool Point::operator==(Point coords) const {
    return this->x == coords.x && this->y == coords.y;
}
