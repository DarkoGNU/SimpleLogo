#include "Interpreter.h"

#include <algorithm>

#include "LuaBridge/LuaBridge.h"
#include "Parser.h"
#include "Writer.h"

namespace lb = luabridge;

Interpreter::Interpreter(const int argc, char const *const argv[])
    : status(params.readParams(argc, argv)), tilemap(params.getSize()),
      turtle(tilemap) {}

bool Interpreter::bad() const { return !status; }

bool Interpreter::execute() {
    Parser parser(params.getInputPath());

    if (!parser.parse()) {
        status = false;
        return false;
    }

    // Initialize the VM
    std::unique_ptr<lua_State, lua_Closer> L(luaL_newstate());
    luaL_openlibs(L.get());

    // Register Turtle class and its functions
    lb::getGlobalNamespace(L.get())
        .beginClass<Turtle>("Turtle")
        .addFunction("przod", &Turtle::forward)
        .addFunction("tyl", &Turtle::back)
        .addFunction("prawo", &Turtle::right)
        .addFunction("lewo", &Turtle::left)
        .endClass();

    // Register turtle
    lb::push(L.get(), &turtle);
    lua_setglobal(L.get(), "turtle");

    // Execute the code and check the result
    if (luaL_dostring(L.get(), parser.getLua().c_str()) != LUA_OK) {
        std::cerr << lua_tostring(L.get(),-1) << '\n';

        status = false;
        return false;
    }

    // Write the TileMap
    if (!writeMap()) {
        status = false;
        return false;
    }

    return true;
}

bool Interpreter::writeMap() const {
    std::string extension = params.getOutputPath().extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   ::tolower);

    if (extension == ".png") {
        return Writer::writePng(params.getOutputPath(), tilemap.getTiles(),
                                tilemap.getSize());
    }

    return Writer::writeText(params.getOutputPath(), tilemap.toString());
}
