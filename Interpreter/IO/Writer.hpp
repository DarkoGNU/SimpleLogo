#pragma once

#include <filesystem>
#include <string_view>

#include <png++/png.hpp>

namespace Writer {
bool writeText(const std::filesystem::path &outputPath, std::string_view text);

// The task demands a BMP file (optional feature), but I'm too lazy
// so I just write a PNG file using PNG++
bool writePng(const std::filesystem::path &outputPath,
              const std::vector<bool> &tiles, unsigned int size);

} // namespace Writer
