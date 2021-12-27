#include "TurtleCommand.hpp"

TurtleCommand::TurtleCommand(std::string code,
                             const std::unordered_set<std::string> &procedures)
    : name(getName(code)), type(getType(procedures)),
      comparison(getComparison(code)), args(getArgs(code)) {}

std::string TurtleCommand::getName(std::string &code) {
    std::stringstream ss(code);
    std::string cmdName;
    std::getline(ss, cmdName, ' ');

    std::stringstream temp;
    temp << ss.rdbuf();
    code = temp.str();

    return cmdName;
}

TurtleCommand::Type
TurtleCommand::getType(const std::unordered_set<std::string> &procedures) {
    if (name == "przod")
        return TurtleCommand::Type::forward;
    else if (name == "tyl")
        return TurtleCommand::Type::back;
    else if (name == "prawo")
        return TurtleCommand::Type::right;
    else if (name == "lewo")
        return TurtleCommand::Type::left;
    else if (name == "if")
        return TurtleCommand::Type::conditional;
    else if (name == "end")
        return TurtleCommand::Type::end;
    else
        return procedures.find(name) == procedures.end()
                   ? TurtleCommand::Type::definition
                   : TurtleCommand::Type::call;
}

TurtleCommand::Comparison TurtleCommand::getComparison(std::string &code) {
    if (type != TurtleCommand::Type::conditional)
        return TurtleCommand::Comparison::null;

    TurtleCommand::Comparison exprType;
    std::size_t index;

    if (index = code.find("<>"); index != std::string::npos)
        exprType = TurtleCommand::Comparison::inequal;
    else if (index = code.find(">"); index != std::string::npos)
        exprType = TurtleCommand::Comparison::greater;
    else if (index = code.find("<"); index != std::string::npos)
        exprType = TurtleCommand::Comparison::less;
    else if (index = code.find("="); index != std::string::npos)
        exprType = TurtleCommand::Comparison::equal;
    else
        return TurtleCommand::Comparison::null;

    if (exprType != TurtleCommand::Comparison::inequal) {
        code[index] = ' ';
    } else {
        code.erase(index, 1);
        code[index] = ' ';
    }

    return exprType;
}

std::vector<Arg> TurtleCommand::getArgs(std::string &code) {
    std::stringstream ss(code);
    std::vector<Arg> nArgs;
    std::string arg;

    while (std::getline(ss, arg, ' '))
        nArgs.emplace_back(Arg(arg));
}
