#pragma once

#include <filesystem>

class Params {
    std::filesystem::path inputPath;
    std::filesystem::path outputPath;
    unsigned int size;

    void help(const char exePath[]);

  public:
    bool readParams(int argc, char const *const argv[]);

    std::filesystem::path getInputPath() const;
    std::filesystem::path getOutputPath() const;
    unsigned int getSize() const;
};
