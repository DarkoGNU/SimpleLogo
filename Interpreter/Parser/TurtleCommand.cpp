#include "TurtleCommand.hpp"

TurtleCommand::TurtleCommand(
    const std::string &code,
    const std::unordered_set<std::string> &procedures) {}

std::string TurtleCommand::getName() {
    std::string cmdName;
    // ss >> cmdName;
    return cmdName;
}

TurtleCommand::Type
TurtleCommand::getType(const std::unordered_set<std::string> &procedures) {
    if (name == "przod")
        return TurtleCommand::Type::forward;
    else if (name == "tyl")
        return TurtleCommand::Type::back;
    else if (name == "prawo")
        return TurtleCommand::Type::right;
    else if (name == "lewo")
        return TurtleCommand::Type::left;
    else if (name == "if")
        return TurtleCommand::Type::conditional;
    else if (name == "end")
        return TurtleCommand::Type::end;
    else
        return procedures.find(name) == procedures.end()
                   ? TurtleCommand::Type::definition
                   : TurtleCommand::Type::call;
};

TurtleCommand::Comparison TurtleCommand::getComparison() {
    if (type != TurtleCommand::Type::conditional)
        return TurtleCommand::Comparison::null;
}
