#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Arg.hpp"

class TurtleCommand {
  public:
    // Variables
    const enum class Type {
        forward,
        back,
        right,
        left,
        conditional,
        definition,
        call,
        end
    } type;

    const enum class Comparison {
        greater,
        less,
        equal,
        inequal,
        null
    } comparison;

    const std::string name;
    const std::vector<Arg> args;

    // Methods
    TurtleCommand(std::string code, std::unordered_set<std::string>& procedures);
};
