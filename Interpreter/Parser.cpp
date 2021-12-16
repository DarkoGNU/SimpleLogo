#include "Parser.h"

#include <cstddef>
#include <regex>
#include <sstream>

#include <iostream> // Debug

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::string Parser::getLua() const { return luaCode; }

bool Parser::parse() {
    std::ifstream file(inputPath);

    if (!readFile(file))
        return false;

    return true;
}

bool Parser::readFile(std::ifstream &file) {
    if (file.bad())
        return false;

    std::stringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();
    std::stringstream().swap(ss); // clear the stream

    if (file.bad())
        return false;

    cleanString(content);
    tokenize(content);
    return true;
}

void Parser::tokenize(const std::string &text) {
    std::string token;
    std::stringstream ss(text);

    while(getline(ss, token, ';')) {
        tokens.push_back(token);
    }

    for (auto& str : tokens) {
        std::cout << str << "\n";
    }
}

void Parser::cleanString(std::string &text) {
    // Replace ) with );
    std::regex pattern(R"(\))");
    text = std::regex_replace(text, pattern, ");");

    // Remove whitespace
    pattern = R"(\s)";
    text = std::regex_replace(text, pattern, "");

    // Get rid of double semicolons
    pattern = R"(;+)";
    text = std::regex_replace(text, pattern, ";");

    // Replace end[name] with just end
    pattern = R"(end[^\s;]*;)";
    text = std::regex_replace(text, pattern, "end;");
}
