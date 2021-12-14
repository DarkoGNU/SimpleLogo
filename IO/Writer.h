#pragma once

#include <filesystem>
#include <string>

namespace Writer {
bool writeText(const std::filesystem::path &outputPath,
                      const std::string &text);

} // namespace Writer
