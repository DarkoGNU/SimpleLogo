#pragma once

#include <filesystem>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

class Parser {
    const std::filesystem::path inputPath;
    std::vector<std::pair<std::string, unsigned int>> simpleTokens;

    std::unordered_set<std::string> registered;
    std::vector<std::pair<std::vector<std::string>, unsigned int>> tokens;

    bool readFile();
    void tokenize(const std::string &text);
    void transformTokens();

    void secondStage();
    void firstStep();
    void secondStep();
    void thirdStep();

    static void cleanString(std::string &text);
    static void transformToken(std::string &text);

  public:
    Parser(std::filesystem::path inputPath);
    bool parse();

    const static std::unordered_set<std::string> builtIn;
    const std::vector<std::pair<std::vector<std::string>, unsigned int>>& getTokens() const;
    const std::unordered_set<std::string>& getRegistered() const;
};
