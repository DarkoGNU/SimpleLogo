#pragma once

#include "Turtle.h"

class SimpleCommand {
    enum class Type { przod, tyl, lewo, prawo };
    Type type;

    double arg;

  public:
    SimpleCommand(Type type, double arg);
    void execute(Turtle turtle;);
};
