#include <iostream>

#include "Params.h"
#include "TileMap.h"
#include "Turtle.h"
#include "Writer.h"

int main(int argc, char *argv[]) {
    std::cout << "Working...\n";

    Params params;

    if (!params.readParams(argc, argv)) {
        return 1;
    }

    unsigned int size = params.getSize();

    TileMap tileMap(size);

    Turtle turtle(tileMap);

    turtle.forward(25);

    Writer::writePng("Test.png", tileMap.getTiles(), params.getSize());
    Writer::writeText("Text.txt", tileMap.toString());
}
