#include "tilemap.h"

TileMap::TileMap(unsigned int size) {
    // tiles[x][y] = tiles[x * size + y]
    tiles = new bool[size * size];
}

TileMap::~TileMap() {
    delete [] tiles;
}