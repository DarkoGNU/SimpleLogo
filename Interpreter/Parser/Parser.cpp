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

Parser::Parser(std::filesystem::path inputPath)
    : inputPath(std::move(inputPath)) {}

std::vector<std::vector<Cmd>> Parser::getCode() const { return code; }

std::vector<std::vector<Cmd>> &Parser::getCodeRef() { return code; }

bool Parser::parse() {
    // Basic splitting
    std::vector<std::string> simpleTokens = SimpleLexer::tokenize(readFile());

    if (simpleTokens.empty())
        return false;

    // Split it further
    DeepLexer deepLexer(std::move(simpleTokens));
    deepLexer.tokenize();
    code = std::move(deepLexer.getCodeRef());

    return !code.empty();
}

std::string Parser::readFile() const {
    std::ifstream file(inputPath,
                       std::ios::in | std::ios::binary | std::ios::ate);

    if (file.fail())
        return std::string();

    std::string content;
    content.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());

    if (file.fail())
        return std::string();

    return content;
}
