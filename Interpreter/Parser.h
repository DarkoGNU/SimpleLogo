#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Parser {
    const std::filesystem::path inputPath;
    std::vector<std::string> tokens;

    bool readFile();
    void tokenize(const std::string &text);
    void transformTokens();

    static void cleanString(std::string &text);
    static void transformToken(std::string &text);

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();
};
