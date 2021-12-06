#include <iostream>

#include "Params.h"
#include "TileMap.h"
#include "Turtle.h"

int main(int argc, char *argv[]) {
    std::cout << "Working...\n";

    Params params;

    if (!params.readParams(argc, argv)) {
        return 1;
    }

    unsigned int size = params.size;

    TileMap tileMap(size);

    Turtle turtle(tileMap);
}
