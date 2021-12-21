#pragma once

#include <unordered_map>
#include <vector>

#include "Parser.h"
#include "Turtle.h"

class Executor {
    Parser &parser;
    Turtle &turtle;
    const std::vector<std::pair<std::vector<std::string>, unsigned int>>
        &tokens;
    std::unordered_map<std::string, unsigned int> procedureMap;

    void registerProcedures();

    void executeCommand(std::string type,
                        std::unordered_map<std::string, double> &argMap);
    double evaluate(std::string expression,
                    std::unordered_map<std::string, double> &argMap);

  public:
    Executor(Turtle &turtle, Parser &parser);
    void execute();
};
