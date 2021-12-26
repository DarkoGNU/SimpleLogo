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

    void execute(const std::vector<Command>& commands, const std::vector<Arg>& args);
    void executeConditional(const std::vector<Command>& commands, const std::vector<Arg>& args, unsigned int& start);

    double evaluateArg(const Arg& arg, const std::vector<Arg>& args);
    bool evaluateCondition(const Command& conditional, const std::vector<Arg>& args);

  public:
    Executor(const std::vector<std::vector<Command>> &code, Turtle &turtle);
    void execute();
};
