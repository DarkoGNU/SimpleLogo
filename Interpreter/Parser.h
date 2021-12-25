#pragma once

#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>

#include "Command.h"
#include "Params.h"

class Parser {
    // Variables
    const std::filesystem::path inputPath;
    std::unordered_set<std::string> procedures;
    std::vector<std::vector<Command>> code;
    bool status;

    // Methods
    std::string readFile() const;
    void tokenize(std::string &codeString);
    static void cleanString(std::string &text);
    void processTokens(std::vector<std::string> &simpleTokens);
    std::vector<Command>

    processProcedure(std::vector<std::string> &simpleTokens,
                     unsigned int &start);

    std::vector<Command>
    processConditional(std::vector<std::string> &simpleTokens,
                       unsigned int &start);

    static Arg processArg(const std::string &expression);
    Command::Type getType(const std::string &command);

    std::vector<std::string> getParts(const std::string &token,
                                      std::string &name, Command::Type &type);

    std::vector<Arg> getArgs(const std::vector<std::string>& parts);

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();

    bool bad() const;
    std::vector<std::vector<Command>> const &getCode() const;
};
