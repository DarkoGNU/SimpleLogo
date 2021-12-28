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
    auto nArgMap = std::unordered_map<std::string, double>();
    call(code[0], nArgMap);
}

void Executor::call(std::vector<TurtleCommand> const &current,
                    std::unordered_map<std::string, double> &argMap) {

    for (unsigned int i = 1; i < current.size(); i++)
        handleCommand(current[i], argMap, i);
}

void Executor::handleCommand(TurtleCommand const &current,
                             std::unordered_map<std::string, double> &argMap,
                             unsigned int &pos) {

    if (current.type == TurtleCommand::Type::call) {
        auto index = procedureMap[current.name];
        auto const &procedure = code[index];
        auto const &definition = procedure[0];

        auto map = getArgMap(definition, current, argMap);
        call(procedure, map);
    }
}

std::unordered_map<std::string, double>
Executor::getArgMap(TurtleCommand const &definition,
                    TurtleCommand const &current,
                    std::unordered_map<std::string, double> &argMap) {

    std::unordered_map<std::string, double> nArgMap;
    for (unsigned int i = 0; i < current.args.size(); i++)
        nArgMap[definition.args[i].name] = evaluateArg(current.args[i], argMap);

    return nArgMap;
}
