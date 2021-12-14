#pragma once

#include <filesystem>
#include <string>

#include <png++/png.hpp>

namespace Writer {
bool writeText(const std::filesystem::path &outputPath,
               const std::string &text);

// The task demands a BMP file, but I'm too lazy to write a BMP encoder
// so I just write a PNG file using a C++ wrapper for libpng
bool writePng(const std::filesystem::path &outputPath,
              const std::vector<bool> &tiles, unsigned int size);

} // namespace Writer
