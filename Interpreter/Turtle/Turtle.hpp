/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include "TileMap.hpp"

/**
 * @brief Represents a turtle.
 * The Turtle can step on a TileMap
 */
class Turtle {
    /**
     * @brief Reference to the TileMap on which Turtle steps.
     * Appropriate lifetime for the TileMap needs to be ensured
     */
    TileMap &tileMap;

    /**
     * @brief Turtle's horizontal position.
     * Will be rounded down to int when stepping
     */
    double x;
    /**
     * @brief Turtle's vertical position.
     * Will be rounded down to int when stepping
     */
    double y;

    /**
     * @brief Turtle's angle in radians.
     * Angle >= 0 && angle < 2π
     */
    double angle;

  public:
    /**
     * @brief Construct a new Turtle object
     *
     * @param tileMap one-dimensional TileMap
     */
    Turtle(TileMap &tileMap);
    /**
     * @brief Construct a new Turtle object
     *
     * @param tileMap one-dimensional TileMap
     * @param startX initial X
     * @param startY initial Y
     * @param startAngle initial angle
     */
    Turtle(TileMap &tileMap, unsigned int startX, unsigned int startY,
           double startAngle);

    /**
     * @brief Turns left.
     *
     * @param turnAngle in degrees
     */
    void left(double turnAngle);
    /**
     * @brief Turns right.
     *
     * @param turnAngle in degrees
     */
    void right(double turnAngle);

    /**
     * @brief Goes forward.
     *
     * @param length in tiles
     */
    void forward(double length);
    /**
     * @brief Goes backward.
     *
     * @param length in tiles
     */
    void back(double length);
};
