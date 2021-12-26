#include "SimpleLexer.hpp"

#include <regex>

SimpleLexer::SimpleLexer(const std::string &codeString)
    : ss{getStream(codeString)} {}

const std::vector<std::string> &SimpleLexer::getTokens() const {
    return simpleTokens;
}

std::stringstream SimpleLexer::getStream(const std::string &text) {
    // Replace ) with );
    const static std::regex pattern1{R"(\)[^;])"};
    return std::stringstream{regex_replace(text, pattern1, ");")};
}

void SimpleLexer::tokenize() {
    std::string token;

    while (std::getline(ss, token, ';'))
        simpleTokens.push_back(token);
}
