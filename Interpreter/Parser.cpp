#include "Parser.h"

#include <cstddef>
#include <regex>
#include <sstream>
#include <stdexcept>

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
    translate(tokens);

    for (auto &token : tokens)
        std::cout << token << "\n";

    return true;
}

void Parser::tokenize(const std::string &text) {
    std::string token;
    std::stringstream ss(text);

    while (getline(ss, token, ';')) {
        tokens.push_back(token);
    }
}

void Parser::translate(std::vector<std::string> &tokens) {
    for (std::string &token : tokens) {
        translate(token);
    }
}

void Parser::translate(std::string &token) {
    if (builtIn.find(token) == builtIn.end()) {
        handleBuiltIn(token);
    }
}

void Parser::handleBuiltIn(std::string &token) {
    std::size_t index = token.find('(');

    std::string type = token.substr(0, index);

    if (type == "przod")
        token.replace(0, index, "turtle.forward");
    else if (type == "tyl")
        token.replace(0, index, "turtle.back");
    else if (type == "prawo")
        token.replace(0, index, "turtle.right");
    else if (type == "lewo")
        token.replace(0, index, "turtle.left");
    else if (type == "if") {
        // Replace () with spaces
        const static std::regex pattern1(R"([()])");
        token = std::regex_replace(token, pattern1, " ");
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
