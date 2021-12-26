#pragma once

#include <string>
#include <unordered_set>
#include <vector>

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
    TurtleCommand(const std::string &code,
                  const std::unordered_set<std::string> &procedures);
};
