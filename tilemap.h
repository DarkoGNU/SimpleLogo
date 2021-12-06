#pragma once

class TileMap {
private:
    unsigned int size;
    bool *tiles;

public:
    TileMap(unsigned int size);
    ~TileMap();

    void step(unsigned int x, unsigned int y);
    unsigned int getSize();
};
