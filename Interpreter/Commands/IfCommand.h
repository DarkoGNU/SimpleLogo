#pragma once

#include <vector>

#include "Command.h"

class IfCommand : public Command {
    std::vector<Command> commands;
};
