/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "Executor.hpp"

#include <cstdlib> // we don't need whole <cmath> for std::abs
#include <stdexcept>
#include <utility>

Executor::Executor(std::vector<std::vector<Cmd>> code, Turtle &turtle)
    : turtle(turtle), procedureMap(createProcedureMap(code)) {}

std::unordered_map<std::string, std::vector<Cmd>>
Executor::createProcedureMap(std::vector<std::vector<Cmd>> code) {

    std::unordered_map<std::string, std::vector<Cmd>> nProcedureMap;

    for (auto &procedure : code)
        nProcedureMap.emplace(procedure[0].name, std::move(procedure));

    return nProcedureMap;
}

void Executor::execute() {
    auto nArgMap = std::unordered_map<std::string, double>();
    call(procedureMap["main"], nArgMap);
}

void Executor::call(std::vector<Cmd> const &procedure,
                    std::unordered_map<std::string, double> &argMap) {

    for (unsigned int i = 1; i < procedure.size(); i++)
        handleCommand(procedure, argMap, i);
}

void Executor::handleCommand(std::vector<Cmd> const &procedure,
                             std::unordered_map<std::string, double> &argMap,
                             unsigned int &pos) {

    auto const &current = procedure[pos];
    double value;

    switch (current.type) {
    case (Cmd::Type::call):
        handleCall(current, argMap);
        return;
    case (Cmd::Type::conditional):
        handleConditional(procedure, argMap, pos);
        return;
    case (Cmd::Type::end):
        return;
    default:
        value = evaluateArg(current.args[0], argMap);
    }

    switch (current.type) {
    case (Cmd::Type::forward):
        turtle.forward(value);
        break;
    case (Cmd::Type::back):
        turtle.back(value);
        break;
    case (Cmd::Type::right):
        turtle.right(value);
        break;
    case (Cmd::Type::left):
        turtle.left(value);
        break;
    default:
        throw std::runtime_error("Unrecognized command");
    }
}

void Executor::handleCall(Cmd const &current,
                          std::unordered_map<std::string, double> &argMap) {

    auto const &procedure = procedureMap[current.name];
    auto const &definition = procedure[0];

    auto map = getArgMap(definition, current, argMap);
    call(procedure, map);
}

void Executor::handleConditional(
    std::vector<Cmd> const &procedure,
    std::unordered_map<std::string, double> &argMap, unsigned int &pos) {

    auto const &current = procedure[pos];

    if (!evaluateComparison(current.args[0], current.args[1],
                            current.comparison, argMap)) {
        while (procedure[++pos].type != Cmd::Type::end)
            continue;
    } else {
        while (procedure[++pos].type != Cmd::Type::end)
            handleCommand(procedure, argMap, pos);
    }
}

std::unordered_map<std::string, double>
Executor::getArgMap(Cmd const &definition,
                    Cmd const &current,
                    std::unordered_map<std::string, double> &argMap) {

    std::unordered_map<std::string, double> nArgMap;

    for (unsigned int i = 0; i < current.args.size(); i++)
        nArgMap.emplace(definition.args[i].name,
                        evaluateArg(current.args[i], argMap));

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
    case (Arg::Operation::divide):
        return argMap[arg.name] / arg.value;
    case (Arg::Operation::add):
        return argMap[arg.name] * arg.value;
    case (Arg::Operation::subtract):
        return argMap[arg.name] - arg.value;
    default:
        throw std::runtime_error("The argument's operation is unknown");
    }
}

bool Executor::evaluateComparison(
    Arg const &first, Arg const &second, Cmd::Comparison type,
    std::unordered_map<std::string, double> &argMap) {

    double firstValue = evaluateArg(first, argMap);
    double secondValue = evaluateArg(second, argMap);

    switch (type) {
    case (Cmd::Comparison::equal):
        return compare(firstValue, secondValue);
    case (Cmd::Comparison::inequal):
        return !compare(firstValue, secondValue);
    case (Cmd::Comparison::greater):
        return firstValue > secondValue;
    case (Cmd::Comparison::less):
        return firstValue < secondValue;
    default:
        throw std::runtime_error("This comparison can't be evaluated");
    }
}

bool Executor::compare(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}
