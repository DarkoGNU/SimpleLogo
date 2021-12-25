#pragma once

#include <list>
#include <string>

struct Command;
struct Arg;

struct Command {
    enum Type {
        forward,
        back,
        right,
        left,
        conditional,
        definition,
        call,
        end
    } type;

    std::string name;
    std::vector<Arg> args;

    // < - less than, > - greater than, = - equal, ! - inequal. Applies only to
    // conditionals
    char comparison;
};

struct Arg {
    // = - just a value, : - just a name
    char operation;
    std::string name;
    double value;
};
