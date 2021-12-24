#pragma once

#include <string>
#include <vector>

struct Command {
    enum Type { forward, back, right, left, conditional, definition, call, end };
    Type type;

    std::string name;
    std::vector<Arg> args;
};

struct Arg {
    // = - just a value, : - just a name
    char operation;

    std::string name;
    double value;
};
