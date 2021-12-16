# Set the project name
project (Commands)

# Add a library with the sources
add_library(${PROJECT_NAME} Simple.cpp Complex.cpp Conditional.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Link the libraries
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC Turtle)
