#pragma once

#include <string>
#include <vector>

class SimpleLexer {
    // Methods
    static std::string cleanString(std::string const &code);

  public:
    static std::vector<std::string> tokenize(std::string const &code);
};
