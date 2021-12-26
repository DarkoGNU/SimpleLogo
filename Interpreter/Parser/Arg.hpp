#pragma once

#include <string>

class Arg {
  public:
    // Variables
    enum class Operation {
        multiply,
        add,
        subtract,
        name,
        value
    };

    Arg::Operation operation;
    std::string name;
    double value;

    // Methods
    Arg();
};
