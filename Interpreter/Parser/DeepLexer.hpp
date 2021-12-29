#pragma once

#include <cstddef>
#include <unordered_set>
#include <vector>

#include "TurtleCommand.hpp"

/**
 * @brief Parses individual Turtle commands.
 */
class DeepLexer {
    /**
     * @brief Command strings to parse.
     */
    std::vector<std::string> simpleTokens;

    /**
     * @brief Parsed commands.
     */
    std::vector<std::vector<TurtleCommand>> code;
    /**
     * @brief Defined procedures.
     * Includes a default main procedure
     */
    std::unordered_set<std::string> procedures;
    /**
     * @brief Currently parsed command.
     */
    std::size_t pos{0};
    /**
     * @brief Currently parsed procedure.
     */
    std::size_t proc{0};

    /**
     * @brief Preprocess a string for parsing.
     *
     * @param token string containing a command
     * @return std::string
     */
    static std::string cleanToken(std::string token);

    /**
     * @brief Clean & return currently parsed command string.
     *
     * @return std::string
     */
    std::string getCleanToken() const;
    /**
     * @brief Constructs and returns currently parsed command.
     *
     * @return TurtleCommand
     */
    TurtleCommand getCommand() const;

    /**
     * @brief Handles procedure parsing.
     */
    void handleProcedure();
    /**
     * @brief Handles parsing of conditional statements.
     */
    void handleConditional();
    /**
     * @brief Handles parsing of procedures and conditional statements.
     * Returns false if the block of code doesn't have an ending
     *
     * @return bool
     */
    bool handleComplex();

  public:
    /**
     * @brief Construct a new DeepLexer object.
     *
     * @param simpleTokens command strings to parse
     */
    DeepLexer(std::vector<std::string> simpleTokens);
    /**
     * @brief Parses all commands.
     */
    void tokenize();

    /**
     * @brief Get parsed code.
     *
     * @return std::vector<std::vector<TurtleCommand>>
     */
    std::vector<std::vector<TurtleCommand>> getCode() const;
};
