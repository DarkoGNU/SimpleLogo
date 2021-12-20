#include "Parser.h"

#include <cstddef>
#include <fstream>
#include <iostream> // debug
#include <regex>
#include <sstream>
#include <unordered_set>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

bool Parser::parse() {

    if (!readFile())
        return false;

    for (auto &test : tokens) {
        std::cout << test.first << ", " << test.second << '\n';
    }

    return true;
}

bool Parser::readFile() {
    std::ifstream file(inputPath);

    if (file.bad())
        return false;

    std::string content;
    {
        std::stringstream ss;
        ss << file.rdbuf();
        content = ss.str();
    }

    if (file.bad())
        return false;

    cleanString(content);
    tokenize(content);
    transformTokens();
    secondStage();

    return true;
}

void Parser::tokenize(const std::string &text) {
    std::string token;
    std::stringstream ss(text);

    while (getline(ss, token, ';')) {
        tokens.push_back(std::make_pair(token, 0));
    }
}

void Parser::transformTokens() {
    for (auto &token : tokens) {
        transformToken(token.first);
    }
}

void Parser::cleanString(std::string &text) {
    // Replace ) with );
    const static std::regex pattern1(R"(\)[^;])");
    text = std::regex_replace(text, pattern1, ");");

    // Remove whitespace
    const static std::regex pattern2(R"(\s)");
    text = std::regex_replace(text, pattern2, "");
}

void Parser::transformToken(std::string &text) {
    // First step - replace the first ( with space, erase the last )
    std::size_t index1 = text.find_first_of('(');

    if (index1 == std::string::npos) {
        // Only "end" doesn't have parentheses. Simplify
        text = "end";
        return;
    }

    std::size_t index2 = text.find_first_of(')');

    if (index2 == std::string::npos)
        return;

    text[index1] = ' ';
    text.pop_back(); // erase the last )

    // Second step - replace comas with spaces
    const static std::regex pattern1(R"(,)");
    text = std::regex_replace(text, pattern1, " ");
}

void Parser::secondStage() {
    firstStep();
    secondStep();
}

void Parser::firstStep() {
    const static std::unordered_set<std::string> builtIn{
        "przod", "tyl", "prawo", "lewo", "if", "end"};
    std::unordered_set<std::string> registered;

    // Set token.second to 1 for function calls
    // Set token.second to 2 for conditionals
    // Set token.second to 3 for ends
    for (auto &token : tokens) {
        // Handle ends
        if (token.first == "end") {
            token.second = 3;
            continue;
        }

        // Handle built-in commands
        std::string type =
            token.first.substr(0, token.first.find_first_of(' '));

        if (builtIn.find(type) != builtIn.end()) {
            if (type != "if")
                continue;
            else
                token.second = 2;
        }

        // Handle function definitions
        if (registered.find(type) != registered.end())
            token.second = 1;
        else
            registered.insert(type);
    }
}

void Parser::secondStep() {
    // Set token.second to place of return
    for (int i = 0; i < tokens.size(); i++) {
        auto &token = tokens[i];

        // Skip ends and things that don't need a place of return
        if (token.second == 0 || token.second == 3)
            continue;

        // Handle function calls (the easiest case)
        if (token.second == 1) {
            token.second = i + 1;
            continue;
        }

        // Handle conditionals (token.second == 2)
        int status = 1;

        for (int x = i + 1; x < tokens.size(); x++) {
            if (tokens[x].second == 2)
                status++;
            else if (tokens[x].second == 3)
                status--;

            if (status == 0) {
                token.second = x;
                break;
            }
        }
    }
}
