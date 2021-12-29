#pragma once

#include <unordered_map>
#include <vector>

#include "Arg.hpp"
#include "Turtle.hpp"
#include "TurtleCommand.hpp"

/**
 * @brief Provides Logo code execution.
 */
class Executor {
    /**
     * @brief The code is executed on this Turtle.
     */
    Turtle &turtle;

    /**
     * @brief Stores vectors containing Logo code.
     * Has to be initialized before procedureMap
     */
    const std::vector<std::vector<TurtleCommand>> code;
    /**
     * @brief Stores the indexes of Logo procedures in the code vector.
     * Has to be initialized after code
     */
    std::unordered_map<std::string, unsigned int> procedureMap;

    /**
     * @brief Create a procedureMap.
     * Depends on code being initialized
     *
     * @return std::unordered_map<std::string, unsigned int>
     */
    std::unordered_map<std::string, unsigned int> createProcedureMap() const;

    /**
     * @brief Executes a procedure.
     *
     * @param procedure the procedure's code
     * @param argMap the arguments and their values
     */
    void call(std::vector<TurtleCommand> const &procedure,
              std::unordered_map<std::string, double> &argMap);
    /**
     * @brief Handles a Logo command.
     * Pos is passed as a reference and can be modified
     *
     * @param procedure the procedure to which the command belongs
     * @param argMap current procedure's arguments
     * @param pos the command's location in the procedure
     */
    void handleCommand(std::vector<TurtleCommand> const &procedure,
                       std::unordered_map<std::string, double> &argMap,
                       unsigned int &pos);
    /**
     * @brief Handles a procedure call.
     *
     * @param current the call
     * @param argMap current procedure's arguments
     */
    void handleCall(TurtleCommand const &current,
                    std::unordered_map<std::string, double> &argMap);
    /**
     * @brief Handles a conditional statement (an if).
     * Pos is passed as a reference and can be modified
     *
     * @param procedure the procedure to which the conditional belongs
     * @param argMap current procedure's arguments
     * @param pos the conditional's location in the procedure
     */
    void handleConditional(std::vector<TurtleCommand> const &procedure,
                           std::unordered_map<std::string, double> &argMap,
                           unsigned int &pos);

    /**
     * @brief Creates an argMap for a procedure call.
     *
     * @param definition the procedure's definition
     * @param current the procedure call
     * @param argMap current procedure's arguments
     * @return std::unordered_map<std::string, double>
     */
    static std::unordered_map<std::string, double>
    getArgMap(TurtleCommand const &definition, TurtleCommand const &current,
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
                       TurtleCommand::Comparison type,
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
    Executor(std::vector<std::vector<TurtleCommand>> code, Turtle &turtle);
    /**
     * @brief Executes the code on the turtle.
     */
    void execute();
};
