#include "Executor.h"

#include <iostream> // debug

Executor::Executor(Turtle &turtle, Parser &parser)
    : turtle(turtle), parser(parser), tokens(parser.getTokens()) {}

void Executor::execute() { registerProcedures(); }

void Executor::registerProcedures() {
    const auto &registered = parser.getRegistered();

    for (int i = 0; i < tokens.size(); i++) {
        const auto &type = tokens[i].first[0];

        if (registered.find(type) != registered.end() && tokens[i].second == 0)
            procedureMap.emplace(type, i);
    }
}
