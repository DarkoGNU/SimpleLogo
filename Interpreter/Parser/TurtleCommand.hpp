#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "Arg.hpp"

/**
 * @brief Represents a Logo's command.
 */
class TurtleCommand {
  public:
    /**
     * @brief The command's type.
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
     * @brief Command's name.
     * Has to be initialized before type
     */
    const std::string name;
    /**
     * @brief Command's type.
     * Has to be initialized after name
     */
    const TurtleCommand::Type type;
    /**
     * @brief Command's comparison.
     * Has to be initialized after name
     */
    const TurtleCommand::Comparison comparison;
    /**
     * @brief Command's arguments.
     * Has to be initialized after comparison
     */
    const std::vector<Arg> args;

    /**
     * @brief Construct a new TurtleCommand object
     *
     * @param code string representing the command
     * @param procedures used to determine whether it's a definition or call
     */
    TurtleCommand(std::string code,
                  const std::unordered_set<std::string> &procedures);

  private:
    /**
     * @brief Get the name for the constructor.
     * Has to be called before getType.
     * The string will be modified
     *
     * @param code reference to string representing the command
     * @return std::string
     */
    std::string getName(std::string &code);
    /**
     * @brief Get the type for the constructor.
     * Depends on name being initialized.
     * The name won't be modified
     *
     * @param procedures already defined procedures
     * @return TurtleCommand::Type
     */
    TurtleCommand::Type
    getType(const std::unordered_set<std::string> &procedures);
    /**
     * @brief Get the type of comparison for the constructor.
     * Has to be called before getArgs.
     * The string may be modified
     *
     * @param code reference to string representing the command
     * @return TurtleCommand::Comparison
     */
    TurtleCommand::Comparison getComparison(std::string &code);
    /**
     * @brief Get the arguments for the constructor.
     * Has to be called after getComparison.
     * The string won't be modified
     *
     * @param code reference to string representing the command
     * @return std::vector<Arg>
     */
    std::vector<Arg> getArgs(const std::string &code);
};
