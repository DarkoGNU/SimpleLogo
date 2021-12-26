#pragma once

#include <sstream>
#include <string>
#include <vector>

class SimpleLexer {
    // Variables
    std::stringstream ss;
    std::vector<std::string> simpleTokens;

    // Methods
    static std::stringstream getStream(const std::string &text);

  public:
    SimpleLexer(const std::string &codeString);

    void tokenize();
    const std::vector<std::string> &getTokens() const;
};
