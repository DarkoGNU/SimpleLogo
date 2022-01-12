/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

#include "Arg.hpp"
#include "Cmd.hpp"
#include "Turtle.hpp"

/**
 * @brief Provides Logo code execution.
 */
class Executor {
    /**
     * @brief The code is executed on this Turtle.
     */
    Turtle &turtle;

    /**
     * @brief Maps procedure names to full procedures.
     * Stores the source code
     */
    std::unordered_map<std::string, std::vector<Cmd>> procedureMap;

    /**
     * @brief Create a procedureMap for the constructor.
     *
     * @param code the source code
     * @return std::unordered_map<std::string, std::vector<Cmd>>
     */
    static std::unordered_map<std::string, std::vector<Cmd>>
    createProcedureMap(std::vector<std::vector<Cmd>> code);

    /**
     * @brief Executes a procedure.
     *
     * @param procedure the procedure's code
     * @param argMap the arguments and their values
     */
    void call(std::vector<Cmd> const &procedure,
              std::unordered_map<std::string, double> &argMap);
    /**
     * @brief Handles a Logo command.
     * Pos is passed as a reference and can be modified
     *
     * @param procedure the procedure to which the command belongs
     * @param argMap current procedure's arguments
     * @param pos the command's location in the procedure
     */
    void handleCommand(std::vector<Cmd> const &procedure,
                       std::unordered_map<std::string, double> &argMap,
                       std::size_t &pos);
    /**
     * @brief Handles a procedure call.
     *
     * @param current the call
     * @param argMap current procedure's arguments
     */
    void handleCall(Cmd const &current,
                    std::unordered_map<std::string, double> &argMap);
    /**
     * @brief Handles a conditional statement (an if).
     * Pos is passed as a reference and can be modified
     *
     * @param procedure the procedure to which the conditional belongs
     * @param argMap current procedure's arguments
     * @param pos the conditional's location in the procedure
     */
    void handleConditional(std::vector<Cmd> const &procedure,
                           std::unordered_map<std::string, double> &argMap,
                           std::size_t &pos);

    /**
     * @brief Creates an argMap for a procedure call.
     *
     * @param definition the procedure's definition
     * @param current the procedure call
     * @param argMap current procedure's arguments
     * @return std::unordered_map<std::string, double>
     */
    static std::unordered_map<std::string, double>
    getArgMap(Cmd const &definition, Cmd const &current,
              std::unordered_map<std::string, double> &argMap);

    /**
     * @brief Evaluates an argument.
     * The argument can be an operation,
     * a simple variable or a constant value.
     *
     * @param arg the argument to be evaluated
     * @param argMap current procedure's argument
     * @return double
     */
    static double evaluateArg(Arg const &arg,
                              std::unordered_map<std::string, double> &argMap);
    /**
     * @brief Evaluates a comparison.
     *
     * @param first the first argument
     * @param second the second argument
     * @param type type of the comparison
     * @param argMap current procedure's arguments
     * @return bool
     */
    static bool
    evaluateComparison(Arg const &first, Arg const &second,
                       Cmd::Comparison type,
                       std::unordered_map<std::string, double> &argMap);

    /**
     * @brief Properly checks whether two doubles are equal.
     *
     * @param a the first value
     * @param b the second value
     * @param epsilon the value by which they can differ
     * @return bool
     */
    static bool compare(double a, double b, double epsilon = 0.01);

  public:
    /**
     * @brief Construct a new Executor object.
     * The Turtle is stored as a reference and will be modified.
     * Appropriate lifetime for the Turtle needs to be ensured.
     *
     * @param code the code
     * @param turtle reference to a Turtle
     */
    Executor(std::vector<std::vector<Cmd>> code, Turtle &turtle);

    /**
     * @brief Executes the code on the turtle.
     */
    void execute();
};
