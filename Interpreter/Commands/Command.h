#pragma once

#include "Turtle.h"

class Command {
  public:
    virtual void execute(Turtle &turtle) = 0;
};
