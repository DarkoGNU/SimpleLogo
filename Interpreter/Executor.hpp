#pragma once

#include <vector>
#include <unordered_map>

#include "Command.hpp"
#include "Turtle.hpp"

class Executor {
    // Variables
    const std::vector<std::vector<Command>> &code;
    Turtle &turtle;

    std::unordered_map<std::string, unsigned int> procedureMap;

    // Methods
    void createProcedureMap();

  public:
    Executor(const std::vector<std::vector<Command>> &code, Turtle &turtle);
};
