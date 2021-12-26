#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Command.hpp"

class Parser {
    // Variables
    const std::filesystem::path inputPath;
    std::vector<std::vector<Command>> code;

    // Methods
    std::string readFile() const;

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();

    std::vector<std::vector<Command>> const &getCode() const;
};
