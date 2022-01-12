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

    const Cmd::Type type;
    const Cmd::Comparison comparison;
    const std::string name;
    const std::vector<Arg> args;

    Cmd(std::string const &code,
              std::unordered_set<std::string> const &procedures);

  private:
    static const std::unordered_map<std::string, Cmd::Type> typeMap;

    Cmd(std::tuple<Cmd::Type, Cmd::Comparison, std::string,
                         std::vector<Arg>>
                  vars);

    static std::tuple<Cmd::Type, Cmd::Comparison, std::string,
                      std::vector<Arg>>
    createCommand(std::string const &code,
                  std::unordered_set<std::string> const &procedures);

    static std::tuple<Cmd::Type, Cmd::Comparison, std::string,
                      std::vector<Arg>>
    handleConditional(std::string const &name, std::string const &expr);

    Cmd::Type getType(const std::unordered_set<std::string> &procedures);

    Cmd::Comparison getComparison(std::string &code);

    std::vector<Arg> getArgs(const std::string &code);
};
