#include "TurtleCommand.hpp"

TurtleCommand::TurtleCommand(std::string code, std::unordered_set<std::string>& procedures)
    : type(TurtleCommand::Type::definition), comparison(TurtleCommand::Comparison::less) {}
