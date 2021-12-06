#pragma once

#include "tilemap.h"

class Turtle {
    TileMap tileMap;

    unsigned int x;
    unsigned int y;
    double angle;

public:
    Turtle(TileMap& tileMap, unsigned int startX, unsigned int startY, double startAngle);

};
