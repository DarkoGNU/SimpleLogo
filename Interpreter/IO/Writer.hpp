#pragma once

#include <filesystem>
#include <string_view>

#include <png++/png.hpp>

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
bool writeText(const std::filesystem::path &outputPath, std::string_view text);

/**
 * @brief Writes a PNG file.
 * Returns false if something went wrong.
 *
 * @param outputPath path to the output file
 * @param tiles tiles to write (2D mapped onto 1D)
 * @param size length and width of tiles
 * @return bool
 */
bool writePng(const std::filesystem::path &outputPath,
              const std::vector<bool> &tiles, unsigned int size);

} // namespace Writer
