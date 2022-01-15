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

using varTuple =
    std::tuple<Cmd::Type, Cmd::Comparison, std::string, std::vector<Arg>>;

// The public constructor
Cmd::Cmd(std::string const &code,
         std::unordered_set<std::string> const &procedures)
    : Cmd{createCommand(code, procedures)} {}

// The delegated constructor
Cmd::Cmd(varTuple vars)
    : type{std::get<0>(vars)}, comparison{std::get<1>(vars)},
      name{std::move(std::get<2>(vars))}, args{std::move(std::get<3>(vars))} {}

// The almighty tuple creator :)
varTuple Cmd::createCommand(std::string const &code,
                            std::unordered_set<std::string> const &procedures) {

    // Split the command
    auto parts = splitCommand(code);

    // Get its type
    Cmd::Type type = getType(parts[0], procedures);

    // Special treatment for conditionals
    if (type == Cmd::Type::conditional)
        return handleConditional(parts[0], parts[1]);

    // Handle args
    std::vector<Arg> nArgs;
    for (std::size_t i = 1; i < parts.size(); i++)
        nArgs.emplace_back(Arg(parts[i]));

    return std::make_tuple(type, Cmd::Comparison::null, std::move(parts[0]),
                           std::move(nArgs));
}

std::vector<std::string> Cmd::splitCommand(std::string const &code) {
    std::stringstream ss(code);
    std::vector<std::string> parts;

    std::string token;
    while (std::getline(ss, token, ' '))
        parts.emplace_back(std::move(token));

    return parts;
}

Cmd::Type Cmd::getType(std::string const &name,
                       std::unordered_set<std::string> const &procedures) {
    auto typeIt = typeMap.find(name);

    // If not found, decide whether it's a definition or a call
    if (typeIt == typeMap.end())
        return procedures.find(name) == procedures.end() ? Cmd::Type::definition
                                                         : Cmd::Type::call;
    else
        return typeIt->second;
}

varTuple Cmd::handleConditional(std::string const &name,
                                std::string const &expr) {
    Cmd::Comparison exprType;
    std::size_t index;

    if (index = expr.find("<>"); index != std::string::npos)
        exprType = Cmd::Comparison::inequal;
    else if (index = expr.find('>'); index != std::string::npos)
        exprType = Cmd::Comparison::greater;
    else if (index = expr.find('<'); index != std::string::npos)
        exprType = Cmd::Comparison::less;
    else if (index = expr.find('='); index != std::string::npos)
        exprType = Cmd::Comparison::equal;
    else
        throw std::runtime_error("Unknown comparison type");

    // Just assign the first argument
    std::string arg1 = expr.substr(0, index);
    // The second one needs a check
    std::string arg2 = exprType == Cmd::Comparison::inequal
                           ? expr.substr(index + 2)
                           : expr.substr(index + 1);

    return std::make_tuple(Cmd::Type::conditional, exprType, name,
                           std::vector<Arg>{Arg(arg1), Arg(arg2)});
}

const std::unordered_map<std::string, Cmd::Type> Cmd::typeMap{
    {"przod", Cmd::Type::forward},      {"forward", Cmd::Type::forward},
    {"tyl", Cmd::Type::back},           {"back", Cmd::Type::back},
    {"prawo", Cmd::Type::right},        {"right", Cmd::Type::right},
    {"lewo", Cmd::Type::left},          {"left", Cmd::Type::left},
    {"jezeli", Cmd::Type::conditional}, {"if", Cmd::Type::conditional},
    {"koniec", Cmd::Type::end},         {"end", Cmd::Type::end},
};
