#pragma once

class TileMap {
    unsigned int size;
    bool *tiles;

  public:
    TileMap(unsigned int size);
    ~TileMap();

    void step(unsigned int x, unsigned int y);
    unsigned int getSize();
};
