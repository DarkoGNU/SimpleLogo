#include "Parser.h"

#include <cstddef> // not sure
#include <regex>
#include <sstream>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

bool Parser::parse() {
    std::ifstream file(inputPath);

    if (!readFile(file))
        return false;

    return true;
}

bool Parser::readFile(std::ifstream &file) {
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

    return true;
}

void Parser::tokenize(const std::string &text) {
    std::string token;
    std::stringstream ss(text);

    while (getline(ss, token, ';')) {
        tokens.push_back(token);
    }
}

void Parser::cleanString(std::string &text) {
    // Replace ) with );
    const static std::regex pattern1(R"(\))");
    text = std::regex_replace(text, pattern1, ");");

    // Remove whitespace
    const static std::regex pattern2(R"(\s)");
    text = std::regex_replace(text, pattern2, "");

    // Get rid of double semicolons
    const static std::regex pattern3(R"(;+)");
    text = std::regex_replace(text, pattern3, ";");

    // Replace end[name] with just end
    const static std::regex pattern4(R"(end[^\s;]*;)");
    text = std::regex_replace(text, pattern4, "end;");
}

const std::unordered_set<std::string> Parser::builtIn{"przod", "tyl", "prawo",
                                                      "lewo",  "if",  "end"};
