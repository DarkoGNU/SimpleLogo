#pragma once

#include <vector>
#include <unordered_set>

// Might be moved to .cpp
#include "Command.hpp"
#include "Arg.hpp" //

class DeepLexer {
    // Variables
    std::unordered_set<std::string> procedures;

    // Methods
    std::vector<Command>
    processProcedure(const std::vector<std::string> &simpleTokens,
                     unsigned int &start);

    std::vector<Command>
    processConditional(const std::vector<std::string> &simpleTokens,
                       unsigned int &start);

    std::vector<std::string> getParts(const std::string &token,
                                      std::string &name);
    std::vector<std::string> getParts(const std::string &token,
                                      std::string &name, Command::Type &type);
    std::vector<std::string> getParts(std::string token, char &comparison);

    Command::Type getType(const std::string &command);
    std::vector<Arg> getArgs(const std::vector<std::string> &parts);
    static Arg processArg(const std::string &expression);

  public:
    std::vector<std::vector<Command>> tokenize(std::vector<std::string> &simpleTokens);
};
