#include "SimpleCommand.h"

void SimpleCommand::execute(Turtle &turtle) {
    switch (type) {
    case SimpleCommand::przod:
        turtle.forward(arg);
        break;
    case SimpleCommand::tyl:
        turtle.back(arg);
        break;
    case SimpleCommand::prawo:
        turtle.right(arg);
        break;
    case SimpleCommand::lewo:
        turtle.left(arg);
        break;
    }
}
