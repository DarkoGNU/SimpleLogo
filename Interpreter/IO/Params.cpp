#include "Params.hpp"

#include <iostream>

bool Params::readParams(int argc, char const *const argv[]) {
    // we need exactly 7 arguments, including the name of the executable
    if (argc != 7) {
        help(argv[0]);
        return false;
    }

    // read the parameters
    for (int i = 1; i < argc; i += 2) {
        std::string type = argv[i];
        std::string value = argv[i + 1];

        if (value.empty()) {
            help(argv[0]);
            return false;
        }

        if (type == "-i") {
            inputPath = std::filesystem::path(value);
        } else if (type == "-o") {
            outputPath = std::filesystem::path(value);
        } else if (type == "-s") {
            size = std::stoi(value);
        } else {
            help(argv[0]);
            return false;
        }
    }

    return true;
}

void Params::help(const char exePath[]) {
    std::string exeName = std::filesystem::path(exePath).filename().string();

    std::cerr << "Usage: " << exeName
              << " -i <input path> -o <output path> -s <size> \n";
}

std::filesystem::path Params::getInputPath() const { return inputPath; }

std::filesystem::path Params::getOutputPath() const { return outputPath; }

unsigned int Params::getSize() const { return size; }
