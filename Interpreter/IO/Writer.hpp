/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <filesystem>
#include <string_view>
#include <vector>

/**
 * @brief Provides methods for writing text files and images.
 */
namespace Writer {
/**
 * @brief Writes a text file.
 * Returns false if something went wrong.
 *
 * @param outputPath path to the output file
 * @param text text to write
 * @return bool
 */
bool writeText(std::filesystem::path const &outputPath, std::string_view text);

/**
 * @brief Writes a PNG file.
 * Returns false if something went wrong.
 *
 * @param outputPath path to the output file
 * @param tiles tiles to write (2D mapped onto 1D)
 * @param size length and width of tiles
 * @return bool
 */
bool writePng(std::filesystem::path const &outputPath,
              std::vector<bool> const &tiles, unsigned int size);

} // namespace Writer
