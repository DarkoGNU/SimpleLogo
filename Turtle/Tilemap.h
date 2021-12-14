#pragma once

#include <string>
#include <vector>

class TileMap {
    const unsigned int size{};

    // Accessing a tile: tiles[y * size + x]
    std::vector<bool> tiles{};

  public:
    TileMap(unsigned int size);
    unsigned int getSize();

    void step(unsigned int x, unsigned int y);

    std::string toString(char stepped = '*', char unstepped = ' ');
};
