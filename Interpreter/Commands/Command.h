#pragma once

#include <memory>

#include "Turtle.h"

class Command {
  public:
    virtual void execute(Turtle &turtle) = 0;
    virtual ~Command() = 0;
};
