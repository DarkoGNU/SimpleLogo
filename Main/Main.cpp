#include <iostream>

#include "Interpreter.h"

int main(int argc, char *argv[]) {
    Interpreter interpreter(argc, argv);

    if (interpreter.bad())
        return false;

    return interpreter.execute() ? 0 : 1;
}
