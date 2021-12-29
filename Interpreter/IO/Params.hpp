#pragma once

#include <filesystem>

/**
 * @brief Parses and stores command line arguments.
 */
class Params {
    /**
     * @brief Path to the input file.
     */
    std::filesystem::path inputPath;
    /**
     * @brief Path to the output file.
     */
    std::filesystem::path outputPath;
    /**
     * @brief Length and width of the output.
     */
    unsigned int size;

    /**
     * @brief Help if the arguments are incorrect.
     *
     * @param exePath path to the executable
     */
    static void help(const char exePath[]);

  public:
    /**
     * @brief Parse the arguments.
     *
     * @param argc number of arguments
     * @param argv array of C-style strings (the arguments)
     * @return bool
     */
    bool readParams(int argc, char const *const argv[]);

    /**
     * @brief Get the path to the input file.
     *
     * @return std::filesystem::path
     */
    std::filesystem::path getInputPath() const;
    /**
     * @brief Get the path to the output file.
     *
     * @return std::filesystem::path
     */
    std::filesystem::path getOutputPath() const;
    /**
     * @brief Get the size (length and width) of the output.
     *
     * @return unsigned int
     */
    unsigned int getSize() const;
};
