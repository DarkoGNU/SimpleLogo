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

    void call(std::vector<TurtleCommand> const &procedure,
              std::unordered_map<std::string, double> &argMap);

    void handleCommand(std::vector<TurtleCommand> const &procedure,
                       std::unordered_map<std::string, double> &argMap,
                       unsigned int &pos);
    void handleCall(TurtleCommand const &current,
                    std::unordered_map<std::string, double> &argMap);
    void handleConditional(std::vector<TurtleCommand> const &procedure,
                           std::unordered_map<std::string, double> &argMap,
                           unsigned int &pos);

    std::unordered_map<std::string, double>
    getArgMap(TurtleCommand const &definition, TurtleCommand const &current,
              std::unordered_map<std::string, double> &argMap);

    double evaluateArg(Arg const &arg,
                       std::unordered_map<std::string, double> &argMap);
    bool evaluateComparison(Arg const &first, Arg const &second,
                            TurtleCommand::Comparison type,
                            std::unordered_map<std::string, double> &argMap);

    static bool compare(double a, double b, double epsilon = 0.01);

  public:
    Executor(std::vector<std::vector<TurtleCommand>> code, Turtle &turtle);
    void execute();
};
