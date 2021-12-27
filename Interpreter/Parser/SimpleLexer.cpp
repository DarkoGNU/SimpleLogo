#include "SimpleLexer.hpp"

#include <regex>

std::string SimpleLexer::cleanString(std::string text) {
    // Replace ) with );
    const static std::regex pattern1{R"(\)[^;])"};
    return regex_replace(text, pattern1, ");");
}

std::vector<std::string> SimpleLexer::tokenize(std::string code) {
    std::vector<std::string> simpleTokens;
    std::stringstream ss(cleanString(code));

    std::string token;
    while (std::getline(ss, token, ';'))
        simpleTokens.push_back(token);

    // Because of how std::getline works, there's going to be one empty token
    simpleTokens.pop_back();
    return simpleTokens;
}
