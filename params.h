#include <filesystem>

class Params {
public:
    std::filesystem::path inputPath;
    std::filesystem::path outputPath;
    unsigned int size;

    bool readParams(int argc, char* argv[]);

private:
    void help(char exePath[]);
};
