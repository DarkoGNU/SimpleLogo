#include "Executor.hpp"

Executor::Executor(const std::vector<std::vector<Command>> &code,
                   Turtle &turtle)
    : code(code), turtle(turtle) { createProcedureMap(); }

void Executor::createProcedureMap() {
    for (unsigned int i = 1; i < code.size(); i++) {
        procedureMap[code[i][0].name] = i;
    }
}
