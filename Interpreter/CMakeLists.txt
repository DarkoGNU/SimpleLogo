# Set the project name
project (Interpreter)

# Add a library with the sources
add_library(${PROJECT_NAME} Interpreter.cpp)

# Add subfolders
add_subdirectory(Turtle)
add_subdirectory(IO)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Link the libraries
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC Turtle IO)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Parser.cpp)
