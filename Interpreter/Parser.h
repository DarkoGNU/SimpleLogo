#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <utility>

class Parser {
    const std::filesystem::path inputPath;
    std::vector<std::pair<std::string, unsigned int>> tokens;

    bool readFile();
    void tokenize(const std::string &text);
    void transformTokens();

    void secondStage();
    void firstStep();
    void secondStep();

    static void cleanString(std::string &text);
    static void transformToken(std::string &text);

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();
};
