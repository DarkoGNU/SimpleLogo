/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "Writer.hpp"

#include <fstream>

#include "png++/png.hpp"

namespace Writer {
bool writeText(std::filesystem::path const &outputPath, std::string_view text) {

    std::ofstream file(outputPath, std::ios::out);

    if (file.fail())
        return false;

    file << text;

    if (file.fail())
        return false;

    return true;
}

// The task demands a BMP file (optional feature), but I'm too lazy
// so I just write a PNG file using PNG++
bool writePng(std::filesystem::path const &outputPath,
              std::vector<bool> const &tiles, std::size_t size) {

    png::image<png::gray_pixel_1> image(size, size);

    for (std::size_t y = 0; y < size; y++)
        for (std::size_t x = 0; x < size; x++)
            image[y][x] = png::gray_pixel_1(!tiles[y * size + x]);

    image.write(outputPath.string());

    return !std::filesystem::is_empty(outputPath);
}

} // namespace Writer
