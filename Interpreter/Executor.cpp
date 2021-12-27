#include "Executor.hpp"

Executor::Executor(std::vector<std::vector<TurtleCommand>> code, Turtle &turtle)
    : turtle(turtle), code(code), procedureMap(createProcedureMap()) {}

std::unordered_map<std::string, unsigned int> Executor::createProcedureMap() {
    std::unordered_map<std::string, unsigned int> nProcedureMap;

    for (unsigned int i = 1; i < code.size(); i++)
        nProcedureMap[code[i][0].name] = i;

    return nProcedureMap;
}

void Executor::execute() {
    call(code[0], std::unordered_map<std::string, double>());
}

void Executor::call(std::vector<TurtleCommand> const &current,
                    std::unordered_map<std::string, double> const &argMap) {

    for (unsigned int i = 0; i < current.size(); i++);
        //handleCommand(current[i], argMap, i);
}

void handleCommand(TurtleCommand const &current,
                   std::unordered_map<std::string, double> const &argMap,
                   unsigned int &pos) {}
