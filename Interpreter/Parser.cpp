#include "Parser.hpp"

#include <cctype>
#include <fstream>
#include <list>
#include <regex>
#include <sstream>

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

bool Parser::bad() const { return !status; }

std::vector<std::vector<Command>> const &Parser::getCode() const {
    return code;
}

bool Parser::parse() {
    std::string codeString = readFile();

    if (codeString.empty())
        return false;

    tokenize(codeString);

    return true;
}

std::string Parser::readFile() const {
    std::ifstream file(inputPath);

    if (file.bad())
        return std::string();

    std::stringstream buffer;
    buffer << file.rdbuf();

    if (file.bad())
        return std::string();

    return buffer.str();
}

void Parser::tokenize(std::string &codeString) {
    std::vector<std::string> simpleTokens;

    {
        std::string token;
        std::stringstream ss(codeString);

        while (std::getline(ss, token, ';'))
            simpleTokens.push_back(token);
    }

    processTokens(simpleTokens);
}

void Parser::cleanString(std::string &text) {
    // Replace ) with );
    const static std::regex pattern1(R"(\)[^;])");
    text = std::regex_replace(text, pattern1, ");");

    // Remove whitespace
    const static std::regex pattern2(R"(\s)");
    text = std::regex_replace(text, pattern2, "");
};

void Parser::processTokens(std::vector<std::string> &simpleTokens) {
    std::vector<Command> mainCode;
    code.push_back(mainCode);

    for (unsigned int i = 0; i < simpleTokens.size(); i++) {
        std::string name;
        Command::Type type;
        std::vector<std::string> parts = getParts(simpleTokens[i], name, type);

        // Check if it's a procedure definition
        if (type == Command::definition) {
            code.push_back(processProcedure(simpleTokens, i));
            continue;
        }

        // Check if it is a conditional
        if (type == Command::conditional) {
            std::vector<Command> result;
            mainCode.insert(mainCode.end(), result.begin(), result.end());
            continue;
        }

        // Handle a simple command or a call
        mainCode.emplace_back(Command{type, name, getArgs(parts)});
    }
}

std::vector<Command>
Parser::processProcedure(std::vector<std::string> &simpleTokens,
                         unsigned int &start) {
    std::vector<Command> procedure;

    // Put the definition in the vector
    std::string definition(simpleTokens[start++]);
    std::string name;
    Command::Type type;
    std::vector<Arg> args = getArgs(getParts(definition, name, type));
    procedure.emplace_back(Command{Command::definition, name, args});

    // Handle the rest
}

std::vector<Command> processConditional(std::vector<std::string> &simpleTokens,
                                        unsigned int &start) {}

Arg Parser::processArg(const std::string &expression) {
    char operation;

    if (expression.find('*') != std::string::npos)
        operation = '*';
    else if (expression.find('+') != std::string::npos)
        operation = '+';
    else if (expression.find('-') != std::string::npos)
        operation = '-';
    else {
        if (std::isdigit(expression[0])) {
            return Arg{'=', std::string(), std::stod(expression)};
        } else {
            return Arg{':', expression, 0};
        }
    }

    std::size_t index = expression.find(operation);
    std::string name = expression.substr(0, index);
    double value = std::stod(expression.substr(index, expression.size()));

    return Arg{operation, name, value};
}

std::vector<std::string> Parser::getParts(const std::string &token,
                                          std::string &name,
                                          Command::Type &type) {
    std::stringstream ss(token);

    // Get the name
    std::getline(ss, name, ' ');
    // Get the type
    type = getType(name);

    // Split into parts
    std::vector<std::string> parts;
    std::string part;
    while (std::getline(ss, part, ' '))
        parts.emplace_back(part);

    return parts;
}

std::vector<Arg> Parser::getArgs(const std::vector<std::string> &parts) {
    std::vector<Arg> args;

    for (const std::string &arg : parts)
        args.push_back(processArg(arg));

    return args;
}

Command::Type Parser::getType(const std::string &command) {
    if (command == "przod")
        return Command::forward;
    else if (command == "tyl")
        return Command::back;
    else if (command == "prawo")
        return Command::right;
    else if (command == "lewo")
        return Command::left;
    else if (command == "if")
        return Command::conditional;
    else if (command == "end")
        return Command::end;

    if (procedures.find(command) != procedures.end())
        return Command::call;

    procedures.emplace(command);
    return Command::definition;
}
