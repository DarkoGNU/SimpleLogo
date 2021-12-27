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
    std::size_t position{0};
    std::size_t procedure{0};

    // Methods
    static std::string cleanToken(std::string token);

    std::string getCleanToken();
    TurtleCommand getCommand();

    void handleProcedure();
    void handleConditional(std::size_t currentProcedure = 0);
    bool handleComplex(std::size_t currentProcedure);

  public:
    DeepLexer(std::vector<std::string> simpleTokens);
    void tokenize();

    const std::vector<std::vector<TurtleCommand>> &getCodeRef() const;
    std::vector<std::vector<TurtleCommand>> getCode();
};
