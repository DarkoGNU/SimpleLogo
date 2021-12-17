#include "Interpreter.h"

#include "LuaBridge/LuaBridge.h"
#include "Parser.h"
#include "Writer.h"

#include <iostream> // debug

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

    // Check the code (debug)
    std::cout << parser.getLua() << '\n';

    // Execute the code
    luaL_dostring(L.get(), parser.getLua().c_str());

    // Write the result
    Writer::writePng(params.getOutputPath(), tilemap.getTiles(), tilemap.getSize());

    // Check error
    std::cout << lua_tostring(L.get(),-1) << '\n';

    return true;
}
