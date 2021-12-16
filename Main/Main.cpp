#include <iostream>

#include "Interpreter.h"

int main(int argc, char *argv[]) {
    Interpreter interpreter(argc, argv);

    std::cout << "!!!Test!!!\n\n";

    return interpreter.execute() ? 0 : 1;
}
