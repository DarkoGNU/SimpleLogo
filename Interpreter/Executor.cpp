#include "Executor.hpp"

#include <stdexcept>

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

void Executor::call(std::vector<TurtleCommand> const &procedure,
                    std::unordered_map<std::string, double> &argMap) {

    for (unsigned int i = 1; i < procedure.size(); i++)
        handleCommand(procedure, argMap, i);
}

void Executor::handleCommand(std::vector<TurtleCommand> const &procedure,
                             std::unordered_map<std::string, double> &argMap,
                             unsigned int &pos) {
    auto const &current = procedure[pos];

    switch (current.type) {
    case (TurtleCommand::Type::call):
        handleCall(current, argMap);
        return;
    case (TurtleCommand::Type::conditional):
        handleConditional(procedure, argMap, pos);
        return;
    case (TurtleCommand::Type::end):
        return;
    }

    double value = evaluateArg(current.args[0], argMap);

    switch (current.type) {
    case (TurtleCommand::Type::forward):
        turtle.forward(value);
        return;
    case (TurtleCommand::Type::back):
        turtle.back(value);
        return;
    case (TurtleCommand::Type::right):
        turtle.right(value);
        return;
    case (TurtleCommand::Type::left):
        turtle.left(value);
        return;
    default:
        throw std::runtime_error("Unrecognized command");
    }
}

void Executor::handleCall(TurtleCommand const &current,
                          std::unordered_map<std::string, double> &argMap) {

    auto index = procedureMap[current.name];
    auto const &procedure = code[index];
    auto const &definition = procedure[0];

    auto map = getArgMap(definition, current, argMap);
    call(procedure, map);
}

void Executor::handleConditional(
    std::vector<TurtleCommand> const &procedure,
    std::unordered_map<std::string, double> &argMap, unsigned int &pos) {

    auto const &current = procedure[pos];

    if (!evaluateComparison(current.args[0], current.args[1],
                            current.comparison, argMap)) {
        while (procedure[++pos].type != TurtleCommand::Type::end)
            continue;
    } else {
        while (procedure[++pos].type != TurtleCommand::Type::end)
            handleCommand(procedure, argMap, pos);
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

double Executor::evaluateArg(Arg const &arg,
                             std::unordered_map<std::string, double> &argMap) {
    switch (arg.operation) {
    case (Arg::Operation::value):
        return arg.value;
    case (Arg::Operation::name):
        return argMap[arg.name];
    case (Arg::Operation::multiply):
        return argMap[arg.name] * arg.value;
    case (Arg::Operation::add):
        return argMap[arg.name] * arg.value;
    case (Arg::Operation::subtract):
        return argMap[arg.name] - arg.value;
    default:
        throw std::runtime_error("The argument's operation is unknown");
    }
}

bool Executor::evaluateComparison(
    Arg const &first, Arg const &second, TurtleCommand::Comparison type,
    std::unordered_map<std::string, double> &argMap) {
    double firstValue = evaluateArg(first, argMap);
    double secondValue = evaluateArg(second, argMap);

    switch (type) {
    case (TurtleCommand::Comparison::equal):
        return firstValue == secondValue;
    case (TurtleCommand::Comparison::inequal):
        return firstValue != secondValue;
    case (TurtleCommand::Comparison::greater):
        return firstValue > secondValue;
    case (TurtleCommand::Comparison::less):
        return firstValue < secondValue;
    default:
        throw std::runtime_error("This comparison can't be evaluated");
    }
}
