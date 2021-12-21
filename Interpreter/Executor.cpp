#include "Executor.h"

#include <iostream> // debug

Executor::Executor(Turtle &turtle, Parser &parser)
    : turtle(turtle), parser(parser), tokens(parser.getTokens()) {
    registerProcedures();
}

void Executor::registerProcedures() {
    const auto &registered = parser.getRegistered();

    for (int i = 0; i < tokens.size(); i++) {
        const auto &type = tokens[i].first[0];

        if (registered.find(type) != registered.end() && tokens[i].second == 0)
            procedureMap.emplace(type, i + 1);
    }
}

void Executor::execute() {
    int status = 0;

    for (auto &token : tokens) {
        const auto &type = token.first[0];

        if (procedureMap.find(type) != procedureMap.end() && token.second == 0)
            status++;
        else if (type == "if")
            status++;
        else if (type == "end")
            status--;
    }
}

void Executor::executeCommand(std::string type,
                              std::unordered_map<std::string, double> &argMap) {

}

double Executor::evaluate(std::string expression,
                          std::unordered_map<std::string, double> &argMap) {}
