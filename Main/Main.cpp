#include <iostream>

#include "Interpreter.hpp"

int main(int argc, char *argv[]) {
    Interpreter interpreter(argc, argv);

    return interpreter.execute() ? 0 : 1;
}
