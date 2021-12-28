#include "Arg.hpp"

#include <cctype>
#include <sstream>

Arg::Arg(std::string arg)
    : operation(getOperation(arg)), value(getValue(arg)), name(getName(arg)) {}

Arg::Operation Arg::getOperation(std::string &arg) {
    // If there's an operation, determine its type
    if (auto index = arg.find('*'); index != std::string::npos) {
        arg[index] = ' ';
        return Arg::Operation::multiply;
    } else if (auto index = arg.find('+'); index != std::string::npos) {
        arg[index] = ' ';
        return Arg::Operation::add;
    } else if (auto index = arg.find('-'); index != std::string::npos) {
        arg[index] = ' ';
        return Arg::Operation::subtract;
    }

    // If there's no operation, it's a name/value
    return std::isdigit(arg[0]) ? Arg::Operation::value : Arg::Operation::name;
}

double Arg::getValue(std::string &arg) {
    if (operation == Arg::Operation::name)
        return 0;

    if (operation == Arg::Operation::value)
        return std::stod(arg);

    std::size_t index = arg.find(' ');
    std::string value = arg.substr(index + 1);

    arg.erase(arg.size() - value.size() - 1);

    return std::stod(value);
}

std::string Arg::getName(std::string arg) { return arg; }
