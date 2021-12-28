#pragma once

#include <string>

class Arg {
  public:
    // Variables
    enum class Operation { multiply, divide, add, subtract, name, value };

    // Warning - the order matters!
    const Arg::Operation operation;
    const double value;
    const std::string name;

    // Methods
    Arg(std::string arg);

  private:
    Arg::Operation getOperation(std::string &arg);
    std::string getName(std::string arg);
    double getValue(std::string &arg);
};
