#pragma once

#include "Params.h"
#include "Tilemap.h"
#include "Turtle.h"

class Interpreter {
    Params params;
    TileMap tilemap;
    Turtle turtle;

  public:
    Interpreter(Params &params);
    bool execute();
};
