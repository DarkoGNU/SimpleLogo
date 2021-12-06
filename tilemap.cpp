#include "tilemap.h"

#include <algorithm>
#include <stdexcept>

TileMap::TileMap(unsigned int size) {
    this->size = size;

    if (size == 0) {
        throw std::invalid_argument("TileMap's size must be other than 0");
    }

    // tiles[x][y] = tiles[y * size + x]
    tiles = new bool[size * size];

    std::fill_n(tiles, size * size, false);
}

TileMap::~TileMap() {
    delete [] tiles;
}

void TileMap::step(unsigned int x, unsigned int y) {
    if (x >= size || y >= size) {
        return;
    }

    tiles[y * size + x] = true;
}

unsigned int TileMap::getSize() {
    return size;
}
