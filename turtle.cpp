#include "turtle.h"

Turtle::Turtle(TileMap& tileMap, unsigned int startX, unsigned int startY, double startAngle) :
tileMap(tileMap), x(startX), y(startY), angle(startAngle) {}
