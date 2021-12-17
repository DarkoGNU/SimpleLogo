#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

class Parser {
    static const std::unordered_set<std::string> builtIn;
    std::unordered_set<std::string> registered;

    std::filesystem::path inputPath;
    std::vector<std::string> tokens;
    std::string luaCode;

    bool readFile(std::ifstream &file);
    void tokenize(const std::string &text);

    static void translate(std::vector<std::string>& tokens);
    static void translate(std::string& token);
    static void cleanString(std::string &text);

    static void handleBuiltIn(std::string& token);

  public:
    Parser(std::filesystem::path inputPath);

    bool parse();
    std::string getLua() const;
};
