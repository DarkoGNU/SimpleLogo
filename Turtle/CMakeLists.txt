# Set the project name
project (Turtle)

# Add a library with the sources
add_library(${PROJECT_NAME} Turtle.cpp TileMap.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)
