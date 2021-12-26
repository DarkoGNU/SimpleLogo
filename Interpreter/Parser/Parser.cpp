#include "Parser.hpp"

#include <cctype>
#include <fstream>
#include <list>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "DeepLexer.hpp"
#include "SimpleLexer.hpp"

Parser::Parser(std::filesystem::path inputPath) : inputPath(inputPath) {}

std::vector<std::vector<Command>> const &Parser::getCode() const {
    return code;
}

bool Parser::parse() {
    // Make sure that code is empty
    code.clear();

    // Read the file and tokenize it
    std::string codeString = readFile();

    if (codeString.empty())
        return false;

    std::vector<std::string> simpleTokens = SimpleLexer::tokenize(codeString);

    // Deeper tokenization
    DeepLexer deepLexer;

    for (auto &token : simpleTokens)
        code.emplace_back(Command(token));

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

void Parser::processTokens(const std::vector<std::string> &simpleTokens) {
    // code[0] will store the main code
    code.emplace_back(std::vector<Command>());

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
            std::vector<Command> result = processConditional(simpleTokens, i);
            code[0].insert(code[0].end(), result.begin(), result.end());
            continue;
        }

        // Handle a simple command or a call
        code[0].emplace_back(Command{type, name, getArgs(parts)});
    }
}

std::vector<Command>
Parser::processProcedure(const std::vector<std::string> &simpleTokens,
                         unsigned int &start) {
    std::vector<Command> procedure;

    // Put the definition in the vector
    std::string definition(simpleTokens[start++]);
    std::string name;
    std::vector<Arg> args = getArgs(getParts(definition, name));
    procedure.emplace_back(Command{Command::definition, name, args});

    // Handle the rest
    for (; start < simpleTokens.size(); start++) {
        std::string name;
        Command::Type type;
        std::vector<std::string> parts =
            getParts(simpleTokens[start], name, type);

        if (type == Command::Type::definition)
            throw std::runtime_error(
                "Nested procedure definitions aren't supported");

        // Check if it is a conditional
        if (type == Command::conditional) {
            std::vector<Command> result =
                processConditional(simpleTokens, start);
            procedure.insert(procedure.end(), result.begin(), result.end());
            continue;
        }

        // Handle a simple command or a call
        procedure.emplace_back(Command{type, name, getArgs(parts)});

        // Check if it's "end"
        if (type == Command::Type::end) {
            return procedure;
        }
    }

    throw std::runtime_error("The procedure doesn't have an end");
}

std::vector<Command>
Parser::processConditional(const std::vector<std::string> &simpleTokens,
                           unsigned int &start) {
    std::vector<Command> conditional;

    // Put the conditional in a vector
    std::string definition(simpleTokens[start++]);
    char comparison;
    std::vector<Arg> args = getArgs(getParts(definition, comparison));
    conditional.emplace_back(
        Command{Command::Type::conditional, "if", args, comparison});

    // Handle the rest
    for (; start < simpleTokens.size(); start++) {
        std::string name;
        Command::Type type;
        std::vector<std::string> parts =
            getParts(simpleTokens[start], name, type);

        if (type == Command::Type::definition)
            throw std::runtime_error(
                "Procedures can't be defined inside conditional statements");

        // Check if it is a conditional (it will be handled recursively)
        if (type == Command::conditional) {
            std::vector<Command> result =
                processConditional(simpleTokens, start);
            conditional.insert(conditional.end(), result.begin(), result.end());
            continue;
        }

        // Handle a simple command or a call
        conditional.emplace_back(Command{type, name, getArgs(parts)});

        // Check if it's "end"
        if (type == Command::Type::end) {
            return conditional;
        }
    }

    throw std::runtime_error("The conditional statement doesn't have an end");
}

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
    double value = std::stod(expression.substr(index + 1, expression.size()));

    return Arg{operation, name, value};
}

std::vector<std::string> Parser::getParts(const std::string &token,
                                          std::string &name) {
    Command::Type type;
    return getParts(token, name, type);
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

std::vector<std::string> Parser::getParts(std::string token, char &comparison) {
    std::size_t index;

    if (index = token.find("<>"); index != std::string::npos) {
        comparison = '!';
        token.erase(index + 1);
    } else if (index = token.find('>'); index != std::string::npos)
        comparison = '>';
    else if (index = token.find('='); index != std::string::npos)
        comparison = '=';
    else if (index = token.find('<'); index != std::string::npos)
        comparison = '<';
    else
        throw std::runtime_error(
            "The conditional doesn't contain a valid comparison");

    std::string firstPart(token.begin() + 3, token.begin() + index);
    std::string secondPart(token.begin() + index + 1, token.end());

    return std::vector<std::string>{firstPart, secondPart};
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
