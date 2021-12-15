#include "Interpreter.h"

Interpreter::Interpreter(Params &params)
    : params(params), tilemap(params.getSize()), turtle(tilemap) {}

bool Interpreter::execute() {
    
}