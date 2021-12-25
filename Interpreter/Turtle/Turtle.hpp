#pragma once

#include "TileMap.hpp"

class Turtle {
    TileMap &tileMap;

    // We use doubles, but they will be rounded down when stepping on TileMap
    double x;
    double y;

    // in radians, angle >= 0 && angle < 2π
    double angle;

  public:
    Turtle(TileMap &tileMap);
    Turtle(TileMap &tileMap, unsigned int startX, unsigned int startY,
           double startAngle);

    void left(double turnAngle);
    void right(double turnAngle);

    void forward(double length);
    void back(double length);
};
