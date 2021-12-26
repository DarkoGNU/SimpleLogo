#pragma once

#include <string>

struct Arg {
  public:
    // Variables
    const enum Operation {
        multiply,
        add,
        subtract,
        name,
        value
    } operation;

    const std::string name;
    const double value;

    // Methods
    Arg(std::string& arg);
};
