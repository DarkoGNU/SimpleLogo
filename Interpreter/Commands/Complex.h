#pragma once

#include <memory>
#include <vector>

#include "Command.h"

class Complex : public Command {
    std::vector<std::unique_ptr<Command>> commands;

  public:
    void execute(Turtle &turtle) override;
    void add(std::unique_ptr<Command> command);
};
