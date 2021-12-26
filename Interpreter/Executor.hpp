#pragma once

#include <vector>
#include <unordered_map>

#include "TurtleCommand.hpp"
#include "Turtle.hpp"

class Executor {
    // Variables
    const std::vector<std::vector<TurtleCommand>> &code;
    Turtle &turtle;

    std::unordered_map<std::string, unsigned int> procedureMap;

    // Methods
    void createProcedureMap();

    void execute(const std::vector<TurtleCommand>& TurtleCommands, const std::vector<Arg>& args);
    void executeConditional(const std::vector<TurtleCommand>& TurtleCommands, const std::vector<Arg>& args, unsigned int& start);

    double evaluateArg(const Arg& arg, const std::vector<Arg>& args);
    bool evaluateCondition(const TurtleCommand& conditional, const std::vector<Arg>& args);

  public:
    Executor(const std::vector<std::vector<TurtleCommand>> &code, Turtle &turtle);
    void execute();
};
