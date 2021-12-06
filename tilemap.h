#include <array>

class TileMap {
private:
    unsigned int size;
    bool *tiles;

public:
    TileMap(unsigned int size);
    ~TileMap();

};
