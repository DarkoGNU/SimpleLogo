#pragma once

#include "Command.h"
#include "Complex.h"

class Conditional : public Command {
    bool condition;
    Complex &commands;

  public:
    Conditional(Complex &commands);

    void execute(Turtle &turtle) override;
};
