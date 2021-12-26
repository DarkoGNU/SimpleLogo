#include "Parser.hpp"

#include <fstream>

#include "SimpleLexer.hpp"

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::vector<std::vector<TurtleCommand>> const &Parser::getCode() const {
    return code;
}

bool Parser::parse() {
    // Read the file
    std::string codeString = readFile();

    if (codeString.empty())
        return false;

    // Basic splitting
    SimpleLexer simpleLexer(codeString);
    simpleLexer.tokenize();
    auto simpleTokens = simpleLexer.getTokens();

    // Split it further
    DeepLexer deepLexer(simpleTokens);
    deepLexer.tokenize();
    code = deepLexer.getCode();

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
