#include "DeepLexer.hpp"

#include <algorithm>
#include <cctype>
#include <regex>
#include <stdexcept>

DeepLexer::DeepLexer(std::vector<std::string> simpleTokens)
    : simpleTokens{simpleTokens}, code{std::vector<TurtleCommand>()} {}

std::vector<std::vector<TurtleCommand>> DeepLexer::getCode() const {
    return code;
}

void DeepLexer::tokenize() {
    // code[0] will store the main code
    // code[1] etc. will be procedures
    for (; pos < simpleTokens.size(); pos++) {
        proc = 0;
        auto newCommand = getCommand();

        if (newCommand.type == TurtleCommand::Type::end)
            throw std::runtime_error("There's at least one ending too much");

        if (newCommand.type == TurtleCommand::Type::definition) {
            proc = procedures.size();
            procedures.emplace(newCommand.name);
            code.emplace_back(std::vector<TurtleCommand>());

            code[proc].push_back(newCommand);
            handleProcedure();

        } else if (newCommand.type == TurtleCommand::Type::conditional) {
            code[0].push_back(newCommand);
            handleConditional();

        } else {
            code[0].push_back(newCommand);
        }
    }

    // They aren't needed anymore
    simpleTokens.clear();
    procedures.clear();
}

void DeepLexer::handleProcedure() {
    if (!handleComplex())
        throw std::runtime_error("The procedure doesn't have an ending");
}

void DeepLexer::handleConditional() {
    if (!handleComplex())
        throw std::runtime_error(
            "The conditional statement doesn't have an ending");
}

bool DeepLexer::handleComplex() {
    for (pos++; pos < simpleTokens.size(); pos++) {

        code[proc].push_back(getCommand());
        auto type = code[proc].back().type;

        if (type == TurtleCommand::Type::definition)
            throw std::runtime_error(
                "Nested procedure definitions aren't supported");

        else if (type == TurtleCommand::Type::conditional)
            handleConditional();

        else if (type == TurtleCommand::Type::end)
            return true;
    }

    return false;
}

std::string DeepLexer::getCleanToken() { return cleanToken(simpleTokens[pos]); }

TurtleCommand DeepLexer::getCommand() {
    return TurtleCommand(getCleanToken(), procedures);
}

std::string DeepLexer::cleanToken(std::string token) {
    // If it's end, we don't need any more information
    const static auto endTest = [](char c) { return !std::isspace(c); };
    auto it = std::find_if(token.begin(), token.end(), endTest);
    if (it + 4 <= token.end() && std::string(it, it + 4) == "end ")
        return "end";

    // Remove any whitespace
    const static std::regex pattern1{R"((\s)+)"};
    token = std::regex_replace(token, pattern1, "");

    // Replace (, with spaces
    const static std::regex pattern2{R"([\(,])"};
    token = std::regex_replace(token, pattern2, " ");

    // If there's ), remove it
    if (token.find(')') != std::string::npos)
        token.pop_back();

    return token;
}
