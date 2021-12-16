#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class Parser {
    std::filesystem::path inputPath;

    std::vector<std::string> tokens;
    std::string luaCode;

    bool readFile(std::ifstream &file);
    void cleanString(std::string &text);
    void tokenize(const std::string &text);

  public:
    Parser(std::filesystem::path inputPath);

    bool parse();
    std::string getLua() const;
};
