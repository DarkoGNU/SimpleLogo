#pragma once

#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>

#include "Command.hpp"
#include "Params.hpp"

class Parser {
    // Variables
    const std::filesystem::path inputPath;
    std::unordered_set<std::string> procedures;
    std::vector<std::vector<Command>> code;

    // Methods
    std::string readFile() const;
    static void cleanString(std::string &text);
    void tokenize(const std::string &codeString);

    void processTokens(const std::vector<std::string> &simpleTokens);

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
    Parser(std::filesystem::path inputPath);
    bool parse();

    std::vector<std::vector<Command>> const &getCode() const;
};
