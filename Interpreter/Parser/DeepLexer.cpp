/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "DeepLexer.hpp"

#include <algorithm>
#include <cctype>
#include <regex>
#include <stdexcept>
#include <utility>

DeepLexer::DeepLexer(std::vector<std::string> simpleTokens)
    : simpleTokens{std::move(simpleTokens)} {

    // The main code will be a default main() procedure
    code.emplace_back(std::vector<Cmd>{Cmd("main ", procedures)});
    procedures.emplace("main");
}

std::vector<std::vector<Cmd>> DeepLexer::getCode() const { return code; }

std::vector<std::vector<Cmd>> &DeepLexer::getCodeRef() { return code; }

void DeepLexer::tokenize() {
    // code[0] will store the main code
    // code[1] etc. will be procedures
    for (; pos < simpleTokens.size(); pos++) {
        proc = 0;
        auto newCommand = getCommand();

        if (newCommand.type == Cmd::Type::end)
            throw std::runtime_error("There's at least one ending too much");

        if (newCommand.type == Cmd::Type::definition) {
            proc = procedures.size();
            procedures.emplace(newCommand.name);

            code.emplace_back(std::vector<Cmd>{std::move(newCommand)});
            handleProcedure();

        } else if (newCommand.type == Cmd::Type::conditional) {
            code[0].emplace_back(std::move(newCommand));
            handleConditional();

        } else {
            code[0].emplace_back(std::move(newCommand));
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

        code[proc].emplace_back(getCommand());
        auto type = code[proc].back().type;

        if (type == Cmd::Type::definition)
            throw std::runtime_error(
                "Nested procedure definitions aren't supported");

        else if (type == Cmd::Type::conditional)
            handleConditional();

        else if (type == Cmd::Type::end)
            return true;
    }

    return false;
}

std::string DeepLexer::getCleanToken() const {
    auto token = simpleTokens[pos];
    cleanToken(token);
    return token;
}

Cmd DeepLexer::getCommand() const { return Cmd(getCleanToken(), procedures); }

void DeepLexer::cleanToken(std::string &token) {
    auto const it = std::find_if(token.begin(), token.end(),
                                 [](char c) { return !std::isspace(c); });

    // If it's end, we don't need any more information
    if (it + 4 <= token.end() && std::string(it, it + 4) == "end ")
        token = "end";
    else if (it + 7 <= token.end() && std::string(it, it + 7) == "koniec ")
        token = "koniec";
    else {
        // Remove any whitespace
        const static std::regex pattern1{R"((\s)+)"};
        token = std::regex_replace(token, pattern1, "");

        // Replace (, with spaces
        const static std::regex pattern2{R"([\(,])"};
        token = std::regex_replace(token, pattern2, " ");

        // If there's ), remove it
        if (token.find(')') != std::string::npos)
            token.pop_back();
    }
}
