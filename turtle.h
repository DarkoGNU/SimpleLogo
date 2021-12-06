#pragma once

#include "tilemap.h"

class Turtle {
public:
    Turtle(TileMap tileMap, unsigned int startX, unsigned int startY, double startAngle);

private:
    TileMap tileMap;

    unsigned int x;
    unsigned int y;
    double angle;
};
