/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Provides a method for splitting the source into commands.
 */
namespace SimpleLexer {
/**
 * @brief Splits Logo code into individual commands.
 *
 * @param code Logo code
 * @return std::vector<std::string>
 */
std::vector<std::string> tokenize(std::string const &code);
} // namespace SimpleLexer
