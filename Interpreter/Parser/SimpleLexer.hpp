#pragma once

#include <string>

class SimpleLexer {
    static void cleanString(std::string &text);

  public:
    static std::vector<std::string> tokenize(std::string codeString);
};
