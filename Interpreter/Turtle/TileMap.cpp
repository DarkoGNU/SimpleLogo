/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "TileMap.hpp"

TileMap::TileMap(std::size_t size) : size{size}, tiles(size * size, false) {}

std::size_t TileMap::getSize() const { return size; }

void TileMap::step(std::size_t x, std::size_t y) {
    if (x >= size || y >= size)
        return;

    tiles[y * size + x] = true;
}

std::string TileMap::toString(char stepped, char unstepped) const {
    std::string visualMap;
    visualMap.reserve(size * size + size);

    for (std::size_t y = 0; y < size; y++) {
        for (std::size_t x = 0; x < size; x++) {
            tiles[y * size + x] ? visualMap.push_back(stepped)
                                : visualMap.push_back(unstepped);
        }

        visualMap.push_back('\n');
    }

    return visualMap;
}

std::vector<bool> const &TileMap::getTiles() const { return tiles; }
