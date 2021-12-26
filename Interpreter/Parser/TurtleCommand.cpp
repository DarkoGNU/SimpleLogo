#include "TurtleCommand.hpp"

TurtleCommand::TurtleCommand(const std::string &code,
                             const std::unordered_set<std::string> &procedures)
    : type(TurtleCommand::Type::definition),
      comparison(TurtleCommand::Comparison::less) {}
