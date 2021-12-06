#include "turtle.h"

#include "tilemap.h"

Turtle::Turtle(TileMap tileMap, unsigned int startX, unsigned int startY, double startAngle) {
    this->tileMap = TileMap(100);

    this->x = startX;
    this->y = startY;
    this->angle = startAngle;
}
