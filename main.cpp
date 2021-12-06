#include <iostream>

#include "params.h"

int main(int argc, char* argv[]) {
    std::cout << "Working...\n";

    Params params;

    if (!params.readParams(argc, argv)) {
        return 1;
    }


}
