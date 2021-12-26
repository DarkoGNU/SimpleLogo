# Set the project name
project (Parser)

# Add a library with the sources
add_library(${PROJECT_NAME} Parser.cpp TurtleCommand.cpp Arg.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE
                Parser.hpp Parser.cpp
                TurtleCommand.hpp TurtleCommand.cpp
                Arg.hpp Arg.cpp
                SimpleLexer.hpp SimpleLexer.cpp
                DeepLexer.hpp DeepLexer.cpp)
