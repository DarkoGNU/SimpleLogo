/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#include "Arg.hpp"

#include <cstddef>

// The public constructor
Arg::Arg(std::string const &arg) : Arg{createArg(arg)} {}

// The delegated constructor
Arg::Arg(std::tuple<Arg::Operation, double, std::string> vars)
    : operation{std::get<0>(vars)}, value{std::get<1>(vars)}, name{std::get<2>(
                                                                  vars)} {}

std::tuple<Arg::Operation, double, std::string>
Arg::createArg(std::string const &arg) {
    // Search for an operatiom
    constexpr auto operations = "*/+-";
    std::size_t index = arg.find_first_of(operations);

    // If there's no operation, it's a name/value
    if (index == std::string::npos)
        return std::isdigit(arg[0])
                   ? std::make_tuple(Arg::Operation::value, std::stod(arg),
                                     std::string())
                   : std::make_tuple(Arg::Operation::name, 0.0, arg);

    // Determine the specific
    Arg::Operation operation;
    switch (arg[index]) {
    case ('*'):
        operation = Arg::Operation::multiply;
        break;
    case ('/'):
        operation = Arg::Operation::divide;
        break;
    case ('+'):
        operation = Arg::Operation::add;
        break;
    case ('-'):
        operation = Arg::Operation::subtract;
        break;
    }

    std::string name = arg.substr(0, index);
    double value = std::stod(arg.substr(index + 1));

    return std::make_tuple(operation, value, name);
}
