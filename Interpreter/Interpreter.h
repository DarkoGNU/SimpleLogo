#pragma once

#include "Params.h"
#include "Tilemap.h"
#include "Turtle.h"

class Interpreter {
    Params params;
    bool status;

    TileMap tilemap;
    Turtle turtle;

  public:
    Interpreter(int argc, char const *const argv[]);
    bool bad() const;

    bool execute();
};
