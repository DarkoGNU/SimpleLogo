#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "Complex.h"

class Parser {
    const std::filesystem::path inputPath;

    static const std::unordered_set<std::string> builtIn;
    std::unordered_map<std::string, Complex> registered;
    std::vector<std::string> tokens;

    bool readFile(std::ifstream &file);
    void tokenize(const std::string &text);
    void cleanString(std::string &text);

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();
};
