/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "Parser.hpp"

#include <fstream>
#include <sstream>
#include <utility>

#include "DeepLexer.hpp"
#include "SimpleLexer.hpp"

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::vector<std::vector<Cmd>> Parser::getCode() const { return code; }

std::vector<std::vector<Cmd>> Parser::getCodeRef() { return code; }

bool Parser::parse() {
    // Read the file
    std::string codeString = readFile();

    if (codeString.empty())
        return false;

    // Basic splitting
    std::vector<std::string> simpleTokens = SimpleLexer::tokenize(codeString);

    if (simpleTokens.empty())
        return false;

    // Split it further
    DeepLexer deepLexer(std::move(simpleTokens));
    deepLexer.tokenize();
    code = std::move(deepLexer.getCodeRef());

    return !code.empty();
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
