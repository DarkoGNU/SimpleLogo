#pragma once

#include <string>
#include <vector>

/**
 * @brief Provides a method for splitting the source into commands.
 * Basically, a static class
 */
class SimpleLexer {
    /**
     * @brief Removes comments and ensures that every command ends with
     * semicolon.
     *
     * @param code Logo code
     * @return std::string
     */
    static std::string cleanString(std::string const &code);

  public:
    /**
     * @brief Splits Logo code into individual commands
     *
     * @param code Logo code
     * @return std::vector<std::string>
     */
    static std::vector<std::string> tokenize(std::string const &code);
};
