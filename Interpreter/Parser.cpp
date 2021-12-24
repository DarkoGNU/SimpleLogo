#include "Parser.h"

#include <fstream>
#include <sstream>
#include <regex>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

bool Parser::bad() const { return !status; }

std::vector<std::vector<Command>> const &Parser::getCode() const {
    return code;
}

bool Parser::parse() {
    std::string codeString = readFile();

    if (codeString.empty())
        return false;

    tokenize(codeString);

    return true;
}

std::string Parser::readFile() const {
    std::ifstream file(inputPath);

    if (file.bad())
        return std::string();

    std::stringstream buffer;
    buffer << file.rdbuf();

    if (file.bad())
        return std::string();

    return buffer.str();
}

void Parser::tokenize(std::string& codeString) {
    std::vector<std::string> simpleTokens;

    {
        std::string token;
        std::stringstream ss(codeString);

        while (std::getline(ss, token, ';'))
            simpleTokens.push_back(token);
    }

    processTokens(simpleTokens);
}

void Parser::cleanString(std::string& text) const {
    // Replace ) with );
    const static std::regex pattern1(R"(\)[^;])");
    text = std::regex_replace(text, pattern1, ");");

    // Remove whitespace
    const static std::regex pattern2(R"(\s)");
    text = std::regex_replace(text, pattern2, "");
};

void processTokens(std::vector<std::string>& simpleTokens) {
    
}
