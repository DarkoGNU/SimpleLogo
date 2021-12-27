#include "Executor.hpp"

Executor::Executor(std::vector<std::vector<TurtleCommand>> code, Turtle &turtle)
    : turtle(turtle), code(code), procedureMap(createProcedureMap()) {}

std::unordered_map<std::string, unsigned int> Executor::createProcedureMap() {
    std::unordered_map<std::string, unsigned int> nProcedureMap;

    for (unsigned int i = 1; i < code.size(); i++)
        nProcedureMap[code[i][0].name] = i;

    return nProcedureMap;
}
