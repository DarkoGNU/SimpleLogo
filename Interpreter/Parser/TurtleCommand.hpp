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

    const std::string name;
    const TurtleCommand::Type type;
    const TurtleCommand::Comparison comparison;
    const std::vector<Arg> args;

    // Methods
    TurtleCommand(const std::string &code,
                  const std::unordered_set<std::string> &procedures);

  private:
    // Methods
    TurtleCommand(std::stringstream code,
                  const std::unordered_set<std::string> &procedures);

    std::string getName(std::stringstream &ss);

    TurtleCommand::Type
    getType(const std::unordered_set<std::string> &procedures);

    TurtleCommand::Comparison getComparison(std::stringstream &ss);
};
