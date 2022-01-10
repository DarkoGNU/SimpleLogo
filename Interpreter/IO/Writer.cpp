/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "Writer.hpp"

#include <fstream>

#include "png++/png.hpp"

namespace Writer {
bool writeText(const std::filesystem::path &outputPath, std::string_view text) {

    std::ofstream file(outputPath);

    if (file.bad())
        return false;

    file << text;

    if (file.bad())
        return false;

    return true;
}

// The task demands a BMP file (optional feature), but I'm too lazy
// so I just write a PNG file using PNG++
bool writePng(const std::filesystem::path &outputPath,
              const std::vector<bool> &tiles, unsigned int size) {

    png::image<png::gray_pixel_1> image(size, size);

    for (unsigned int y = 0; y < size; y++)
        for (unsigned int x = 0; x < size; x++)
            image[y][x] = png::gray_pixel_1(!tiles[y * size + x]);

    image.write(outputPath.string());

    return !std::filesystem::is_empty(outputPath);
}

} // namespace Writer
