#include "Parser.hpp"

#include <fstream>

#include "SimpleLexer.hpp"
#include "DeepLexer.hpp"

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::vector<std::vector<TurtleCommand>> const &Parser::getCode() const {
    return code;
}

bool Parser::parse() {
    // Read the file and tokenize it
    std::string codeString = readFile();

    if (codeString.empty())
        return false;

    std::vector<std::string> simpleTokens = SimpleLexer::tokenize(codeString);

    // Deeper tokenization
    DeepLexer deepLexer;

    code = deepLexer.tokenize(simpleTokens);

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
