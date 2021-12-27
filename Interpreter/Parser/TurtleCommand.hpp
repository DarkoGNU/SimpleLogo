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

    // Warning - the order matters!
    const std::string name;
    const TurtleCommand::Type type;
    const TurtleCommand::Comparison comparison;
    const std::vector<Arg> args;

    // Methods
    TurtleCommand(std::string code,
                  const std::unordered_set<std::string> &procedures);

  private:
    // Methods
    std::string getName(std::string &code);
    TurtleCommand::Comparison getComparison(std::string &code);
    std::vector<Arg> getArgs(const std::string &code);

    TurtleCommand::Type
    getType(const std::unordered_set<std::string> &procedures);
};
