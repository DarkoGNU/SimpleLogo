#pragma once

#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "Arg.hpp"

class TurtleCommand {
  public:
    // Variables
    enum class Type {
        forward,
        back,
        right,
        left,
        conditional,
        definition,
        call,
        end
    };

    enum class Comparison { greater, less, equal, inequal, null };

    TurtleCommand::Type type;
    TurtleCommand::Comparison comparison;
    std::string name;
    std::vector<Arg> args;

    // Methods
    TurtleCommand(const std::string &code,
                  const std::unordered_set<std::string> &procedures);

  private:
    // Variables

    // Methods
    std::string getName();

    TurtleCommand::Type
    getType(const std::unordered_set<std::string> &procedures);

    TurtleCommand::Comparison getComparison();
};
