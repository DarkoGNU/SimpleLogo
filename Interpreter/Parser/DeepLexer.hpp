#pragma once

#include <cstddef>
#include <unordered_set>
#include <vector>

#include "TurtleCommand.hpp"

class DeepLexer {
    // Variables
    std::vector<std::string> simpleTokens;

    std::vector<std::vector<TurtleCommand>> code;
    std::unordered_set<std::string> procedures;
    std::size_t pos{0};
    std::size_t proc{0};

    // Methods
    static std::string cleanToken(std::string token);

    std::string getCleanToken();
    TurtleCommand getCommand();

    void handleProcedure();
    void handleConditional();
    bool handleComplex();

  public:
    DeepLexer(std::vector<std::string> simpleTokens);
    void tokenize();

    std::vector<std::vector<TurtleCommand>> getCode() const;
};
