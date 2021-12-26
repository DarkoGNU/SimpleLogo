#pragma once

#include <unordered_set>
#include <vector>

#include "TurtleCommand.hpp"
#include "Arg.hpp"

class DeepLexer {
    // Variables
    std::unordered_set<std::string> procedures;

    // Methods
    static void cleanToken(std::string &token);

  public:
    std::vector<std::vector<TurtleCommand>>
    tokenize(std::vector<std::string> simpleTokens);
};
