#pragma once

#include <memory>

#include "Params.h"
#include "Tilemap.h"
#include "Turtle.h"
#include "lua.hpp"

class Interpreter {
    struct lua_Closer;

    Params params;
    bool status;

    TileMap tilemap;
    Turtle turtle;

  public:
    Interpreter(int argc, char const *const argv[]);
    bool bad() const;

    bool execute();
};

struct Interpreter::lua_Closer {
    void operator()(lua_State *lua) { lua_close(lua); }
};
