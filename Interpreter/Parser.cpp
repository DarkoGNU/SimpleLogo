#include "Parser.h"

#include <cstddef>
#include <fstream>
#include <iostream> // debug
#include <regex>
#include <sstream>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

bool Parser::parse() {

    if (!readFile())
        return false;

    for (auto &test : tokens) {
        std::cout << test.first << "\n";
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
    // First step - replace outermost () with spaces, if the token contains them
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
    text[index2] = ' ';

    // Second step - replace comas with spaces
    const static std::regex pattern1(R"(,)");
    text = std::regex_replace(text, pattern1, " ");
}

void Parser::secondStage() {}
