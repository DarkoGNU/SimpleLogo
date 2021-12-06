#include "Turtle.h"

Turtle::Turtle(TileMap &tileMap)
    : tileMap(tileMap), x(tileMap.getSize() / 2), y(tileMap.getSize() / 2),
      angle(180) {}

Turtle::Turtle(TileMap &tileMap, unsigned int startX, unsigned int startY,
               double startAngle)
    : tileMap(tileMap), x(startX), y(startY), angle(startAngle) {}
