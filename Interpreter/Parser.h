#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

class Parser {
    static const std::unordered_set<std::string> builtIn;
    std::unordered_set<std::string> registered;

    const std::filesystem::path inputPath;
    std::vector<std::string> tokens;

    bool readFile(std::ifstream &file);
    void tokenize(const std::string &text);

    void translate(std::vector<std::string> &tokens);
    void translate(std::string &token);
    void cleanString(std::string &text);

    void handleBuiltIn(std::string &token);

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();
};
