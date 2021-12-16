#pragma once

#include "Command.h"

class Simple: public Command {
    enum Type { forward, back, left, right };
    Type type;

    double arg;

  public:
    void execute(Turtle &turtle) override;
};
