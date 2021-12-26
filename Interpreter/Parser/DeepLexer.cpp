#include "DeepLexer.hpp"

#include <regex>
#include <iostream> //debug

std::vector<std::vector<TurtleCommand>>
DeepLexer::tokenize(std::vector<std::string> simpleTokens) {
    std::vector<std::vector<TurtleCommand>> code;

    // Clean tokens
    for (auto &token : simpleTokens)
        cleanToken(token);
}

void DeepLexer::cleanToken(std::string &token) {
    // If it's end, we don't need more
    if (token.size() >= 5 && token.substr(0, 3) == "end") {
        token = "end";
        return;
    }

    // Remove whitespace
    const static std::regex pattern1(R"((\s)+)");
    token = std::regex_replace(token, pattern1, "");

    // Replace (, with space
    const static std::regex pattern2(R"([\(,])");
    token = std::regex_replace(token, pattern2, "");

    // If there's ), remove it
    if (token.find(')') != std::string::npos)
        token.pop_back();

    std::cout << token << "\n";
}
