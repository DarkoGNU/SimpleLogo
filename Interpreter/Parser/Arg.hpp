#pragma once

#include <string>

/**
 * @brief Represents an argument.
 */
class Arg {
  public:
    /**
     * @brief Possible operation.
     * Name - it's a variable.
     * Value - it's a value
     */
    enum class Operation { multiply, divide, add, subtract, name, value };

    /**
     * @brief The operation.
     * Has to be initialized before value
     */
    const Arg::Operation operation;
    /**
     * @brief The value.
     * Has to be initialized before name
     */
    const double value;
    /**
     * @brief Variable's name.
     * Has to be initialized after value
     */
    const std::string name;

    /**
     * @brief Construct a new Arg
     *
     * @param arg string representing the argument
     */
    Arg(std::string arg);

  private:
    /**
     * @brief Gets the operation for the constructor.
     * Has to be called before getValue.
     * The string will be modified
     *
     * @param arg reference to string representing the argument
     * @return Arg::Operation
     */
    static Arg::Operation getOperation(std::string &arg);
    /**
     * @brief Gets the value for the constructor.
     * Has to be called before initializing name.
     * The string will be modified
     *
     * @param arg reference to string representing the argument
     * @return double
     */
    double getValue(std::string &arg) const;
};
