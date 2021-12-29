#pragma once

#include <string>
#include <vector>

/**
 * @brief Provides a method for splitting the source into commands.
 */
namespace SimpleLexer {

namespace {
/**
 * @brief Removes comments and ensures that
 * every command ends with a semicolon.
 *
 * @param code Logo code
 * @return std::string
 */
std::string cleanString(std::string const &code);
} // namespace

/**
 * @brief Splits Logo code into individual commands.
 *
 * @param code Logo code
 * @return std::vector<std::string>
 */
std::vector<std::string> tokenize(std::string const &code);
}; // namespace SimpleLexer
