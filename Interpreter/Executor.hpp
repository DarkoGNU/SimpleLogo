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
    std::unordered_map<std::string, unsigned int> procedureMap;

    // Methods
    std::unordered_map<std::string, unsigned int> createProcedureMap();
    void call(std::vector<TurtleCommand> const &current,
              std::unordered_map<std::string, double> &argMap);

    void handleCommand(TurtleCommand const &current,
                       std::unordered_map<std::string, double> &argMap,
                       unsigned int &pos);

    std::unordered_map<std::string, double>
    getArgMap(TurtleCommand const &definition, TurtleCommand const &current,
              std::unordered_map<std::string, double> &argMap);

  public:
    Executor(std::vector<std::vector<TurtleCommand>> code, Turtle &turtle);

    void execute();
};
