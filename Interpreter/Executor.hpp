#pragma once

#include <unordered_map>
#include <vector>

#include "Arg.hpp"
#include "Turtle.hpp"
#include "TurtleCommand.hpp"

class Executor {
    // Variables
    Turtle &turtle;

    // Warning - the order matters!
    const std::vector<std::vector<TurtleCommand>> code;
    const std::unordered_map<std::string, unsigned int> procedureMap;

    // Methods
    std::unordered_map<std::string, unsigned int> createProcedureMap();

  public:
    Executor(std::vector<std::vector<TurtleCommand>> code, Turtle &turtle);

    void execute() {};
};
