#include "Interpreter.h"

#include "lua.hpp"
#include "Parser.h"

Interpreter::Interpreter(const int argc, char const *const argv[])
    : status(params.readParams(argc, argv)), tilemap(params.getSize()),
      turtle(tilemap) {}

bool Interpreter::bad() const {
    return !status;
}

bool Interpreter::execute() {
    Parser parser(params.getInputPath());

    if(!parser.parse())
        return false;


    return true;
}
