#include "DeepLexer.hpp"

#include <algorithm>
#include <cctype>
#include <regex>
#include <stdexcept>

DeepLexer::DeepLexer(const std::vector<std::string> &simpleTokens)
    : simpleTokens{simpleTokens}, code{std::vector<TurtleCommand>()} {}

std::vector<std::vector<TurtleCommand>> DeepLexer::getCode() const {
    return code;
}

void DeepLexer::tokenize() {
    // code[0] will store the main code
    // code[1] etc. will be procedures
    for (; position < simpleTokens.size(); position++) {

        auto newCommand = getCommand();

        if (newCommand.type == TurtleCommand::Type::end)
            throw std::runtime_error("There's at least one ending too much");

        if (newCommand.type == TurtleCommand::Type::definition) {
            procedures.emplace(newCommand.name);
            code.emplace_back(std::vector<TurtleCommand>());
            procedure++;

            code[procedure].push_back(newCommand);
            handleProcedure();

        } else if (newCommand.type == TurtleCommand::Type::conditional) {
            code[0].push_back(newCommand);
            handleConditional();

        } else {
            code[0].push_back(newCommand);
        }
    }
}

void DeepLexer::handleProcedure() {
    if (!handleComplex(procedure))
        throw std::runtime_error("The procedure doesn't have an ending");
}

void DeepLexer::handleConditional(std::size_t currentProcedure) {
    if (!handleComplex(currentProcedure))
        throw std::runtime_error(
            "The conditional statement doesn't have an ending");
}

bool DeepLexer::handleComplex(std::size_t currentProcedure) {
    for (position++; position < simpleTokens.size(); position++) {

        code[currentProcedure].push_back(getCommand());
        auto type = code[currentProcedure].back().type;

        if (type == TurtleCommand::Type::definition)
            throw std::runtime_error(
                "Nested procedure definitions aren't supported");

        else if (type == TurtleCommand::Type::conditional)
            handleConditional(procedure);

        else if (type == TurtleCommand::Type::end)
            return true;
    }

    return false;
}

std::string DeepLexer::getCleanToken() {
    return cleanToken(simpleTokens[position]);
}

TurtleCommand DeepLexer::getCommand() {
    return TurtleCommand(getCleanToken(), procedures);
}

std::string DeepLexer::cleanToken(std::string token) {
    // If it's end, we don't need any more information
    const static auto endTest = [](char c) { return !std::isspace(c); };
    auto it = std::find_if(token.begin(), token.end(), endTest);
    if (it + 4 >= token.end() && std::string(it, it + 4) == "end ")
        return "end";

    // Remove any whitespace
    const static std::regex pattern1{R"((\s)+)"};
    token = std::regex_replace(token, pattern1, "");

    // Replace (, with spaces
    const static std::regex pattern2{R"([\(,])"};
    token = std::regex_replace(token, pattern2, "");

    // If there's ), remove it
    if (token.find(')') != std::string::npos)
        token.pop_back();

    return token;
}
