#pragma once

#include <string>
#include <vector>

/**
 * @brief Represents a map of tiles.
 * A Turtle can walk on it, every tile
 * it visits will be marked
 */
class TileMap {
    /**
     * @brief Size of the TileMap.
     * It's both its length and width
     */
    const unsigned int size;
    /**
     * @brief Container storing the state of tiles.
     * A tile is false by default, it becomes true when something steps on it.
     * It maps a 2D structure onto a 1D container.
     * Accessing a tile: tiles[y * size + x]
     */
    std::vector<bool> tiles;

  public:
    /**
     * @brief Construct a new TileMap object.
     *
     * @param size TileMap's size (length and width)
     */
    TileMap(unsigned int size);
    /**
     * @brief Get the TileMap's 2D size.
     *
     * @return unsigned int
     */
    unsigned int getSize() const;

    /**
     * @brief Step on a tile.
     * Parameters should be in range 0 - (size - 1).
     * Else, nothing happens (it won't step out of bounds)
     *
     * @param x the horizontal position
     * @param y the vertical position
     */
    void step(unsigned int x, unsigned int y);

    /**
     * @brief Returns the TileMap as a string.
     *
     * @param stepped used to represent true
     * @param unstepped used to represent false
     * @return std::string
     */
    std::string toString(char stepped = '*', char unstepped = ' ') const;
    /**
     * @brief Get a reference to tiles.
     * It's still a 1D vector representing
     * two dimensions
     *
     * @return const std::vector<bool>&
     */
    const std::vector<bool> &getTiles() const;
};
