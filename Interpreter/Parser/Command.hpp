#pragma once

#include <string>
#include <vector>

#include "DeepLexer.hpp"
#include "Arg.hpp"

class Command {
  public:
    // Variables
    const enum Type {
        forward,
        back,
        right,
        left,
        conditional,
        definition,
        call,
        end
    } type;

    const enum Comparison {
        greater,
        less,
        equal,
        inequal,
        null
    } comparison;

    const std::string name;
    const std::vector<Arg> args;
    
    // Methods
    Command(std::string& code, DeepLexer lexer);
};
