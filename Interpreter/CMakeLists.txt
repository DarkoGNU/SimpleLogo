# Copyright 2021 The SimpleLogo Authors.
# Licensed under GPL-3.0-or-later

# Set the project name
project (Interpreter)

# Add a library with the sources
add_library(${PROJECT_NAME} Interpreter.cpp)

# Add subfolders
add_subdirectory(IO)
add_subdirectory(Parser)
add_subdirectory(Turtle)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Link the libraries
target_link_libraries (${PROJECT_NAME} PUBLIC Turtle IO Parser)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Interpreter.hpp Interpreter.cpp Executor.hpp Executor.cpp)
