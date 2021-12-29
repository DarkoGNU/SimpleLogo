#include "SimpleLexer.hpp"

#include <algorithm>
#include <cstddef>
#include <regex>

namespace SimpleLexer {

namespace {
std::string cleanString(std::string const &text) {
    // Get rid of comments
    std::stringstream ss(text);
    std::string line;
    std::string result;

    while (getline(ss, line)) {
        std::size_t comment = line.find("//");
        if (comment != std::string::npos)
            line.erase(comment);

        result += line;
    }

    // Replace ) with );
    const static std::regex pattern1{R"(\)[^;])"};
    return regex_replace(result, pattern1, ");");
}
} // namespace

std::vector<std::string> tokenize(std::string const &code) {
    std::vector<std::string> simpleTokens;
    std::stringstream ss(cleanString(code));

    std::string token;
    while (std::getline(ss, token, ';'))
        // Safeguard against empty tokens
        if (!std::all_of(token.begin(), token.end(), ::isspace))
            simpleTokens.push_back(token);

    return simpleTokens;
}
} // namespace SimpleLexer
