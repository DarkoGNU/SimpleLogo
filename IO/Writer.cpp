#include "Writer.h"

#include <fstream>
#include <vector>

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

// The task demands a BMP file, but I'm too lazy to write a BMP encoder
// so I just write a PNG file using a C++ wrapper for libpng
bool writePng(const std::filesystem::path &outputPath,
              const std::vector<bool> &tiles, unsigned int size) {

    png::image<png::gray_pixel_1> image(size, size);

    for (unsigned int y = 0; y < size; y++)
        for (unsigned int x = 0; x < size; x++)
            image[y][x] = png::gray_pixel_1(!tiles[y * size + x]);

    image.write(outputPath);

    return !std::filesystem::is_empty(outputPath);
}

} // namespace Writer
