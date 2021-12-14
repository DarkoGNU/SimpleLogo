#include "Writer.h"

#include <fstream>

namespace Writer {
bool writeText(const std::filesystem::path &outputPath,
                      const std::string &text) {

    std::ofstream file(outputPath);

    if (file.bad())
        return false;

    file << text;

    if (file.bad())
        return false;

    return true;
}

} // namespace Writer
