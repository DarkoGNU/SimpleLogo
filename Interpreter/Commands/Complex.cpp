#include "Complex.h"

void Complex::execute(Turtle &turtle) {
    for (auto const &command : commands) {
        command->execute(turtle);
    }
}

void Complex::add(std::unique_ptr<Command> command) {
    commands.push_back(std::move(command));
}
