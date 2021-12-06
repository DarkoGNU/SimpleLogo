#pragma once

#include "TileMap.h"

class Turtle {
    TileMap tileMap;

    unsigned int x;
    unsigned int y;
    double angle;

  public:
    Turtle(TileMap &tileMap);
    Turtle(TileMap &tileMap, unsigned int startX, unsigned int startY,
           double startAngle);
};
