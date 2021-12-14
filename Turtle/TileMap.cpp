#include "TileMap.h"

TileMap::TileMap(unsigned int size) : size{size}, tiles(size * size, false){};

unsigned int TileMap::getSize() { return size; }

void TileMap::step(unsigned int x, unsigned int y) {
    if (x >= size || y >= size)
        return;

    tiles[y * size + x] = true;
}

std::string TileMap::toString(char stepped, char unstepped) const {
    std::string visualMap;
    visualMap.reserve(size * size + size);

    for (unsigned int y = 0; y < size; y++) {
        for (unsigned int x = 0; x < size; x++) {
            tiles[y * size + x] ? visualMap.push_back(stepped)
                                : visualMap.push_back(unstepped);
        }

        visualMap.push_back('\n');
    }

    return visualMap;
}

std::vector<bool> TileMap::getTiles() const { return tiles; }
