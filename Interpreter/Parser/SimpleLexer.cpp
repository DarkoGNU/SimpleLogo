/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "SimpleLexer.hpp"

#include <algorithm>
#include <cstddef>
#include <regex>
#include <sstream>

namespace SimpleLexer {

namespace {
/**
 * @brief Removes comments and ensures that
 * every command ends with a semicolon.
 *
 * @param code Logo code
 * @return std::string
 */
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
    const static std::regex pattern1{R"(\)(?=[^;]))"};
    return regex_replace(result, pattern1, ");");
    // This will double ; in cases like ") ;", but tokenize will deal with it
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
