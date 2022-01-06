/**
 * @file Main.cpp
 * @brief Create an interpreter and execute the code.
 * Main is very simple. First, it constructs an Interpreter, passing
 * command line arguments to the constructors. Then, it calls its execute()
 * method and returns 0 on 1 based on whether it was successful.
 *
 * @license GPLv3
 */
#include "Interpreter.hpp"

/**
 * @brief The main method
 *
 * @param argc the number of arguments
 * @param argv array of C-style strings (the arguments)
 * @return int
 */
int main(int argc, char *argv[]) {
    Interpreter interpreter(argc, argv);

    return interpreter.execute() ? 0 : 1;
}
