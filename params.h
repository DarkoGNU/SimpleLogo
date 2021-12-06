#pragma once

#include <filesystem>

class Params {
    void help(char exePath[]);

public:
    std::filesystem::path inputPath;
    std::filesystem::path outputPath;
    unsigned int size;

    bool readParams(int argc, char* argv[]);
    
};
