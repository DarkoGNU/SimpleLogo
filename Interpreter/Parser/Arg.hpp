/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <string>
#include <tuple>

/**
 * @brief Represents an argument.
 */
class Arg {
  public:
    /**
     * @brief Possible operations.
     * Name - it's just a variable.
     * Value - it's just a value
     */
    enum class Operation { multiply, divide, add, subtract, name, value };

    /**
     * @brief Argument's operation.
     */
    Arg::Operation const operation;
    /**
     * @brief Argument's value.
     */
    double const value;
    /**
     * @brief Argument's name.
     */
    std::string const name;

    /**
     * @brief Construct a new Arg.
     *
     * @param arg string representing the argument
     */
    Arg(std::string const &arg);

  private:
    /**
     * @brief Construct a new Arg object
     *
     * @param vars member variables in a tuple
     */
    Arg(std::tuple<Arg::Operation, double, std::string> vars);

    /**
     * @brief Provides values for the constructor.
     *
     * @param arg string representing the argument
     * @return std::tuple<Arg::Operation, double, std::string>
     */
    static std::tuple<Arg::Operation, double, std::string>
    createArg(std::string const &arg);
};
