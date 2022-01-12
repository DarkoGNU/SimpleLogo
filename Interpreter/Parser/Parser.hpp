/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Cmd.hpp"

/**
 * @brief Provides a simple interface to read and parse Logo source file.
 */
class Parser {
    /**
     * @brief Path to the source file.
     */
    std::filesystem::path const inputPath;
    /**
     * @brief Parsed Logo code.
     */
    std::vector<std::vector<Cmd>> code;

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
     * @param inputPath path to the source file.
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
     * @return std::vector<std::vector<Cmd>> const&
     */
    std::vector<std::vector<Cmd>> getCode() const;

    /**
     * @brief Get parsed code (reference).
     *
     * @return std::vector<std::vector<Cmd>>&
     */
    std::vector<std::vector<Cmd>> &getCodeRef();
};
