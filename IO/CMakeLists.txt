# Set the project name
project (IO)

# Add a library with the sources
add_library(${PROJECT_NAME} Params.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)
