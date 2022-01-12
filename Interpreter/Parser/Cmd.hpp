/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Arg.hpp"

/**
 * @brief Represents a Logo command.
 */
class Cmd {
  public:
    /**
     * @brief Type of the command.
     */
    enum class Type {
        forward,
        back,
        right,
        left,
        conditional,
        definition,
        call,
        end
    };

    /**
     * @brief Comparison type (for conditionals).
     * Null for other types of commands
     */
    enum class Comparison { greater, less, equal, inequal, null };

    /**
     * @brief Type of the command.
     */
    const Cmd::Type type;
    /**
     * @brief Comparison type (for conditionals).
     * Null for other types of command
     */
    const Cmd::Comparison comparison;
    /**
     * @brief Name of the command.
     */
    const std::string name;
    /**
     * @brief Command's arguments.
     */
    const std::vector<Arg> args;

    /**
     * @brief Construct a new Cmd.
     *
     * @param code string representing the command
     * @param procedures already declared procedures
     */
    Cmd(std::string const &code,
        std::unordered_set<std::string> const &procedures);

  private:
    /**
     * @brief Maps strings to command types.
     */
    static const std::unordered_map<std::string, Cmd::Type> typeMap;

    /**
     * @brief Construct a new Cmd.
     *
     * @param vars member variables in a tuple
     */
    Cmd(std::tuple<Cmd::Type, Cmd::Comparison, std::string, std::vector<Arg>>
            vars);

    /**
     * @brief Provides values for the constructor.
     *
     * @param code string representing the command
     * @param procedures already declared procedures
     * @return std::tuple<Cmd::Type, Cmd::Comparison, std::string,
     * std::vector<Arg>>
     */
    static std::tuple<Cmd::Type, Cmd::Comparison, std::string, std::vector<Arg>>
    createCommand(std::string const &code,
                  std::unordered_set<std::string> const &procedures);
    /**
     * @brief Handles a conditional command.
     *
     * @param name name of the command
     * @param expr string representing the comparison
     * @return std::tuple<Cmd::Type, Cmd::Comparison, std::string,
     * std::vector<Arg>>
     */
    static std::tuple<Cmd::Type, Cmd::Comparison, std::string, std::vector<Arg>>
    handleConditional(std::string name, std::string expr);
    /**
     * @brief Splits a command by space.
     *
     * @param code string representing the command
     * @return std::vector<std::string>
     */
    static std::vector<std::string> splitCommand(std::string const &code);
    /**
     * @brief Determines the command's type.
     *
     * @param name name of the command
     * @param procedures already declared procedures
     * @return Cmd::Type
     */
    static Cmd::Type getType(std::string const &name,
                             std::unordered_set<std::string> const &procedures);
};
