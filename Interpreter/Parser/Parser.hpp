#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "TurtleCommand.hpp"

/**
 * @brief Provides a simple interface to read and parse Logo source file.
 */
class Parser {
    /**
     * @brief Path to the source file.
     */
    const std::filesystem::path inputPath;
    /**
     * @brief Parsed Logo code.
     */
    std::vector<std::vector<TurtleCommand>> code;

    /**
     * @brief Reads a text file.
     *
     * @return std::string
     */
    std::string readFile() const;

  public:
    /**
     * @brief Construct a new Parser object
     *
     * @param inputPath Path to the source file.
     */
    Parser(std::filesystem::path inputPath);
    /**
     * @brief Parse the source file.
     *
     * @return bool
     */
    bool parse();

    /**
     * @brief Get parsed code.
     *
     * @return std::vector<std::vector<TurtleCommand>>
     */
    std::vector<std::vector<TurtleCommand>> getCode() const;
};
