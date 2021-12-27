#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "TurtleCommand.hpp"

class Parser {
    // Variables
    const std::filesystem::path inputPath;
    std::vector<std::vector<TurtleCommand>> code;

    // Methods
    std::string readFile() const;

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();

    const std::vector<std::vector<TurtleCommand>> &getCode() const;
};
