/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include "Params.hpp"
#include "TileMap.hpp"
#include "Turtle.hpp"

/**
 * @brief Provides a simple interface for interpreting Logo files.
 */
class Interpreter {

    /**
     * @brief Stores command line arguments.
     * Will be used to get the input path, the output path
     * and determine the TileMap's size
     */
    Params params;
    /**
     * @brief Tells if everything's OK.
     * Becomes false when something goes wrong
     */
    bool status;

    /**
     * @brief The TileMap for the Turtle.
     */
    TileMap tilemap;
    /**
     * @brief The Turtle used when executing Logo code.
     */
    Turtle turtle;

    /**
     * @brief Writes a TileMap.
     * It will determine whether to write a text file or a PNG file
     * based on the file's extension
     */
    void writeMap();

  public:
    /**
     * @brief Construct a new Interpreter object.
     *
     * @param argc number of arguments
     * @param argv an array of C-style strings (the arguments)
     */
    Interpreter(int argc, char const *const argv[]);
    bool bad() const;

    /**
     * @brief Executes the Logo code and writes the result.
     *
     * @return bool
     */
    bool execute();
};
