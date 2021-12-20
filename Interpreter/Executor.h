#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Parser.h"
#include "Turtle.h"

class Executor {
    Parser &parser;
    Turtle &turtle;
    const std::vector<std::pair<std::vector<std::string>, unsigned int>>
        &tokens;
    std::unordered_map<std::string, unsigned int> procedureMap;

    void prepare();

  public:
    Executor(Turtle turtle, Parser parser);
    void execute();
};
