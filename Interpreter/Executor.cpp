#include "Executor.h"

Executor::Executor(Turtle turtle, Parser parser)
    : turtle(turtle), parser(parser), tokens(parser.getTokens()) {}

void Executor::execute() { prepare(); }

void Executor::prepare() {
    for (int i = 0; i < tokens.size(); i++) {
        if (parser.getRegistered().find(tokens[i].first[0]) !=
            parser.getRegistered().end()) {
            procedureMap.emplace(tokens[i].first[0], i);
        }
    }
}
