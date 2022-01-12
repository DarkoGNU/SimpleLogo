/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "Cmd.hpp"

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include <utility>

using varTuple = std::tuple<Cmd::Type, Cmd::Comparison, std::string,
                            std::vector<Arg>>;

// The public constructor
Cmd::Cmd(std::string const &code,
                     std::unordered_set<std::string> const &procedures)
    : Cmd{createCommand(code, procedures)} {}

// The delegated constructor
Cmd::Cmd(varTuple vars)
    : type{std::get<0>(vars)}, comparison{std::get<1>(vars)},
      name{std::get<2>(vars)}, args{std::get<3>(vars)} {}

// The almighty tuple creator :)
varTuple
Cmd::createCommand(std::string const &code,
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
    Cmd::Type type;
    Cmd::Comparison comparison;
    auto typeIt = typeMap.find(name);

    // If not found, decide whether it's a definition or a call
    if (typeIt == typeMap.end())
        type = procedures.find(name) == procedures.end()
                   ? Cmd::Type::definition
                   : Cmd::Type::call;
    else
        type = typeIt->second;

    // Special treatment for conditionals
    if (type == Cmd::Type::conditional)
        return handleConditional(name, parts[1]);
    else
        comparison = Cmd::Comparison::null;

    // Handle args
    std::vector<Arg> nArgs;
    for (unsigned int i = 1; i < parts.size(); i++)
        nArgs.emplace_back(Arg(parts[i]));

    return std::make_tuple(type, comparison, name, nArgs);
}

varTuple Cmd::handleConditional(std::string const& name, std::string const &expr) {
    Cmd::Comparison exprType;
    std::size_t index;

    if (index = expr.find("<>"); index != std::string::npos)
        exprType = Cmd::Comparison::inequal;
    else if (index = expr.find(">"); index != std::string::npos)
        exprType = Cmd::Comparison::greater;
    else if (index = expr.find("<"); index != std::string::npos)
        exprType = Cmd::Comparison::less;
    else if (index = expr.find("="); index != std::string::npos)
        exprType = Cmd::Comparison::equal;
    else
        throw std::runtime_error("Unknown comparison type");

    // Just assign the first argument
    std::string arg1 = expr.substr(0, index);
    // The second one needs a check
    std::string arg2 = exprType == Cmd::Comparison::inequal
                           ? expr.substr(index + 2)
                           : expr.substr(index + 1);

    std::vector nArgs { Arg(arg1), Arg(arg2) };

    return std::make_tuple(Cmd::Type::conditional, exprType, name, nArgs);
}

std::vector<Arg> Cmd::getArgs(const std::string &code) {
    std::stringstream ss(code);
    std::vector<Arg> nArgs;
    std::string arg;

    while (std::getline(ss, arg, ' '))
        nArgs.emplace_back(Arg(arg));

    return nArgs;
}

const std::unordered_map<std::string, Cmd::Type> Cmd::typeMap{
    {"przod", Cmd::Type::forward},
    {"forward", Cmd::Type::forward},
    {"tyl", Cmd::Type::back},
    {"back", Cmd::Type::back},
    {"prawo", Cmd::Type::right},
    {"right", Cmd::Type::right},
    {"lewo", Cmd::Type::left},
    {"left", Cmd::Type::left},
    {"jezeli", Cmd::Type::conditional},
    {"if", Cmd::Type::conditional},
    {"koniec", Cmd::Type::end},
    {"end", Cmd::Type::end},
};
