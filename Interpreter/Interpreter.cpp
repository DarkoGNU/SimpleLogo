#include "Interpreter.h"

Interpreter::Interpreter(const int argc, char const *const argv[])
    : status(params.readParams(argc, argv)), tilemap(params.getSize()),
      turtle(tilemap) {}

bool Interpreter::bad() const {
    return !status;
}

bool Interpreter::execute() {
    
}
