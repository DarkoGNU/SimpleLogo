/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include <tuple>
#include <unordered_map>

#include "Arg.hpp"

/**
 * @brief Represents a Logo command.
 */
class TurtleCommand {
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

    const TurtleCommand::Type type;
    const TurtleCommand::Comparison comparison;
    const std::string name;
    const std::vector<Arg> args;

    TurtleCommand(std::string const &code,
              std::unordered_set<std::string> const &procedures);

  private:
    static const std::unordered_map<std::string, TurtleCommand::Type> typeMap;

    TurtleCommand(std::tuple<TurtleCommand::Type, TurtleCommand::Comparison, std::string,
                         std::vector<Arg>>
                  vars);

    static std::tuple<TurtleCommand::Type, TurtleCommand::Comparison, std::string,
                      std::vector<Arg>>
    createCommand(std::string const &code,
                  std::unordered_set<std::string> const &procedures);

    static std::tuple<TurtleCommand::Type, TurtleCommand::Comparison, std::string,
                      std::vector<Arg>>
    handleConditional(std::string const &name, std::string const &expr);

    TurtleCommand::Type getType(const std::unordered_set<std::string> &procedures);

    TurtleCommand::Comparison getComparison(std::string &code);

    std::vector<Arg> getArgs(const std::string &code);
};
