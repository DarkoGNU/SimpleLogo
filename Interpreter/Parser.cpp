#include "Parser.h"

#include <cstddef>
#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_set>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::vector<std::pair<std::vector<std::string>, unsigned int>> const &
Parser::getTokens() const {
    return tokens;
}

std::unordered_set<std::string> const &Parser::getRegistered() const {
    return registered;
}

bool Parser::parse() {

    if (!readFile())
        return false;

    transformTokens();
    secondStage();

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

    return true;
}

void Parser::cleanString(std::string &text) {
    // Replace ) with );
    const static std::regex pattern1(R"(\)[^;])");
    text = std::regex_replace(text, pattern1, ");");

    // Remove whitespace
    const static std::regex pattern2(R"(\s)");
    text = std::regex_replace(text, pattern2, "");
}

void Parser::tokenize(const std::string &text) {
    std::string token;
    std::stringstream ss(text);

    while (getline(ss, token, ';')) {
        simpleTokens.push_back(std::make_pair(token, 0));
    }
}

void Parser::transformTokens() {
    for (auto &token : simpleTokens) {
        transformToken(token.first);
    }
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
    thirdStep();
}

void Parser::firstStep() {
    // Set token.second to 1 for function calls
    // Set token.second to 2 for conditionals
    // Set token.second to 3 for ends
    for (auto &token : simpleTokens) {
        // Handle ends
        if (token.first == "end") {
            token.second = 3;
            continue;
        }

        // Handle built-in commands
        std::string type =
            token.first.substr(0, token.first.find_first_of(' '));

        if (builtIn.find(type) != builtIn.end()) {
            if (type == "if")
                token.second = 2;

            continue;
        }

        // Handle function definitions
        if (registered.find(type) != registered.end())
            token.second = 1;
        else
            registered.emplace(type);
    }
}

void Parser::secondStep() {
    // Set token.second to place of return
    for (int i = 0; i < simpleTokens.size(); i++) {
        auto &token = simpleTokens[i];

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

        for (int x = i + 1; x < simpleTokens.size(); x++) {
            if (simpleTokens[x].second == 2)
                status++;
            else if (simpleTokens[x].second == 3)
                status--;

            if (status == 0) {
                token.second = x;
                break;
            }
        }
    }
}

void Parser::thirdStep() {
    // Split elements into single words
    for (int i = 0; i < simpleTokens.size(); i++) {
        std::string element;
        std::stringstream ss(simpleTokens[i].first);

        tokens.push_back(
            std::make_pair(std::vector<std::string>(), simpleTokens[i].second));

        while (std::getline(ss, element, ' ')) {
            tokens[i].first.push_back(element);
        }
    }

    // simpleTokens no longer needed
    simpleTokens.clear();
}

const std::unordered_set<std::string> Parser::builtIn{"przod", "tyl", "prawo",
                                                      "lewo",  "if",  "end"};
