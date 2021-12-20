#include "Interpreter.h"

#include <algorithm>

#include "Writer.h"
#include "Parser.h"

Interpreter::Interpreter(const int argc, char const *const argv[])
    : status(params.readParams(argc, argv)), tilemap(params.getSize()),
      turtle(tilemap) {}

bool Interpreter::bad() const { return !status; }

bool Interpreter::execute() {
    Parser parser(params.getInputPath());
    
    parser.parse();

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
