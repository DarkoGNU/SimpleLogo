#include "SimpleLexer.hpp"

#include <regex>

void SimpleLexer::cleanString(std::string &text) {
    // Replace ) with );
    const static std::regex pattern1(R"(\)[^;])");
    text = std::regex_replace(text, pattern1, ");");
}

std::vector<std::string> SimpleLexer::tokenize(std::string codeString) {
    cleanString(codeString);

    std::vector<std::string> simpleTokens;

    {
        std::string token;
        std::stringstream ss(codeString);

        while (std::getline(ss, token, ';'))
            simpleTokens.push_back(token);
    }

    return simpleTokens;
}
