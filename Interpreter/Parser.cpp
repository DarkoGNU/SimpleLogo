#include "Parser.h"

#include <cstddef>
#include <regex>
#include <sstream>
#include <stdexcept>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::string Parser::getLua() const { return luaCode; }

bool Parser::parse() {
    std::ifstream file(inputPath);

    if (!readFile(file))
        return false;

    luaCode.clear();

    for (const std::string &token : tokens)
        luaCode.append(token).push_back(' ');

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
    std::size_t index = token.find('(');
    std::string type = token.substr(0, index);

    if (builtIn.find(type) != builtIn.end()) {
        handleBuiltIn(token);
        return;
    }

    if (registered.find(type) == registered.end()) {
        token.insert(0, "function ");
        registered.insert(type);
    }

    // If it's a call, do nothing. It's already in the correct form
}

void Parser::handleBuiltIn(std::string &token) {
    std::size_t index = token.find('(');
    std::string type = token.substr(0, index);

    if (type == "przod" || type == "tyl" || type == "prawo" || type == "lewo")
        token.insert(0, "turtle:");
    else if (type == "if") {
        // Replace () with spaces
        const static std::regex pattern1(R"([()])");
        token = std::regex_replace(token, pattern1, " ");
        // append "then"
        token += "then";
    }

    // Do nothing if it's "end"
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
