#include "Conditional.h"

Conditional::Conditional(Complex &commands) : commands(commands) {}

void Conditional::execute(Turtle &turtle) {
    if (condition) {
        commands.execute(turtle);
    }
}
