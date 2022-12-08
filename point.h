/*
-----------------------------------------------------------------------------------
Project Name    : lab06-lastrobotstanding-comme_tu_veux
File's Name     : Point.h
Author          :   Aellen Quentin
                    Atasever Mehmet
                    Salamin Chloé
Creation Date   : 02.12.2022
Description     :
Remarque(s)     :
Compiler        : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef ROBOT_POINT_H
#define ROBOT_POINT_H

#include <string>

class Point {
public:
    size_t x, y;

    Point();

    Point(size_t x, size_t y) : x(x), y(y) {}

    explicit operator std::string() const;

    static Point fromStrToPoint(const std::string& coords, const std::string& sep = ",");

    bool operator == (Point coords) const;
};

#endif //ROBOT_POINT_H
