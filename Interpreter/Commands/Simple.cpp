#include "Simple.h"

void Simple::execute(Turtle &turtle) {
    switch (type) {
    case Simple::forward:
        turtle.forward(arg);
        break;
    case Simple::back:
        turtle.back(arg);
        break;
    case Simple::right:
        turtle.right(arg);
        break;
    case Simple::left:
        turtle.left(arg);
        break;
    }
}
