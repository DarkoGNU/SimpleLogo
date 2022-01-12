/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "TurtleCommand.hpp"

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include <utility>

using varTuple = std::tuple<TurtleCommand::Type, TurtleCommand::Comparison, std::string,
                            std::vector<Arg>>;

// The public constructor
TurtleCommand::TurtleCommand(std::string const &code,
                     std::unordered_set<std::string> const &procedures)
    : TurtleCommand{createCommand(code, procedures)} {}

// The delegated constructor
TurtleCommand::TurtleCommand(varTuple vars)
    : type{std::get<0>(vars)}, comparison{std::get<1>(vars)},
      name{std::get<2>(vars)}, args{std::get<3>(vars)} {}

// The almighty tuple creator :)
varTuple
TurtleCommand::createCommand(std::string const &code,
                         std::unordered_set<std::string> const &procedures) {

    // Split the command
    std::stringstream ss(code);
    std::vector<std::string> parts;

    std::string token;
    while (std::getline(ss, token, ' '))
        parts.emplace_back(token);

    // Get its name
    auto const& name = parts[0];

    // Search for the type in typeMap
    TurtleCommand::Type type;
    TurtleCommand::Comparison comparison;
    auto typeIt = typeMap.find(name);

    // If not found, decide whether it's a definition or a call
    if (typeIt == typeMap.end())
        type = procedures.find(name) == procedures.end()
                   ? TurtleCommand::Type::definition
                   : TurtleCommand::Type::call;
    else
        type = typeIt->second;

    // Special treatment for conditionals
    if (type == TurtleCommand::Type::conditional)
        return handleConditional(name, parts[1]);
    else
        comparison = TurtleCommand::Comparison::null;

    // Handle args
    std::vector<Arg> nArgs;
    for (unsigned int i = 1; i < parts.size(); i++)
        nArgs.emplace_back(Arg(parts[i]));

    return std::make_tuple(type, comparison, name, nArgs);
}

varTuple TurtleCommand::handleConditional(std::string const& name, std::string const &expr) {
    TurtleCommand::Comparison exprType;
    std::size_t index;

    if (index = expr.find("<>"); index != std::string::npos)
        exprType = TurtleCommand::Comparison::inequal;
    else if (index = expr.find(">"); index != std::string::npos)
        exprType = TurtleCommand::Comparison::greater;
    else if (index = expr.find("<"); index != std::string::npos)
        exprType = TurtleCommand::Comparison::less;
    else if (index = expr.find("="); index != std::string::npos)
        exprType = TurtleCommand::Comparison::equal;
    else
        throw std::runtime_error("Unknown comparison type");

    // Just assign the first argument
    std::string arg1 = expr.substr(0, index);
    // The second one needs a check
    std::string arg2 = exprType == TurtleCommand::Comparison::inequal
                           ? expr.substr(index + 2)
                           : expr.substr(index + 1);

    std::vector nArgs { Arg(arg1), Arg(arg2) };

    return std::make_tuple(TurtleCommand::Type::conditional, exprType, name, nArgs);
}

std::vector<Arg> TurtleCommand::getArgs(const std::string &code) {
    std::stringstream ss(code);
    std::vector<Arg> nArgs;
    std::string arg;

    while (std::getline(ss, arg, ' '))
        nArgs.emplace_back(Arg(arg));

    return nArgs;
}

const std::unordered_map<std::string, TurtleCommand::Type> TurtleCommand::typeMap{
    {"przod", TurtleCommand::Type::forward},
    {"forward", TurtleCommand::Type::forward},
    {"tyl", TurtleCommand::Type::back},
    {"back", TurtleCommand::Type::back},
    {"prawo", TurtleCommand::Type::right},
    {"right", TurtleCommand::Type::right},
    {"lewo", TurtleCommand::Type::left},
    {"left", TurtleCommand::Type::left},
    {"jezeli", TurtleCommand::Type::conditional},
    {"if", TurtleCommand::Type::conditional},
    {"koniec", TurtleCommand::Type::end},
    {"end", TurtleCommand::Type::end},
};
