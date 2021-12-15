#pragma once

#include "Command.h"

class SimpleCommand : public Command {
    enum Type { przod, tyl, lewo, prawo };

    Type type;
    double arg;

  public:
    void execute(Turtle &turtle);
};
