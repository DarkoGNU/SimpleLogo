#include "Interpreter.hpp"

#include <algorithm>

#include "Executor.hpp"
#include "Parser.hpp"
#include "Writer.hpp"

Interpreter::Interpreter(const int argc, char const *const argv[])
    : status(params.readParams(argc, argv)), tilemap(params.getSize()),
      turtle(tilemap) {}

bool Interpreter::bad() const { return !status; }

bool Interpreter::execute() {
    if (bad())
        return false;

    Parser parser(params.getInputPath());

    if (!parser.parse())
        return false;

    Executor executor(parser.getCode(), turtle);

    return true;
}

bool Interpreter::writeMap() const {
    std::string extension = params.getOutputPath().extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   ::tolower);

    if (extension == ".png") {
        return Writer::writePng(params.getOutputPath(), tilemap.getTiles(),
                                tilemap.getSize());
    }

    return Writer::writeText(params.getOutputPath(), tilemap.toString());
}
