#pragma once

#include <string>

class Arg {
  public:
    // Variables
    enum class Operation { multiply, add, subtract, name, value };

    const Arg::Operation operation;
    const std::string name;
    const double value;

    // Methods
    Arg(const std::string &arg);

  private:
    Arg::Operation getOperation(const std::string &arg);
    std::string getName(const std::string &arg);
    double getValue(const std::string &arg);
};
