#pragma once

#include <vector>
#include <filesystem>
#include <string>

#include "Command.h"
#include "Params.h"

class Parser {
    const std::filesystem::path inputPath;
    std::vector<std::vector<Command>> code;
    bool status;

  public:
    Parser(std::filesystem::path inputPath);
    bool bad() const;
    std::vector<std::vector<Command>> const &getCode() const;

    bool parse();

    std::string readFile() const;
    void tokenize(std::string& codeString);
    void cleanString(std::string& text) const;
    void processTokens(std::vector<std::string>& simpleTokens);
};
