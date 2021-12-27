#include "Arg.hpp"

Arg::Arg(const std::string &arg)
    : operation(getOperation(arg)), name(getName(arg)), value(getValue(arg)) {}

Arg::Operation Arg::getOperation(const std::string &arg) {}

std::string Arg::getName(const std::string &arg) {}

double Arg::getValue(const std::string &arg) {}
