# Set the project name
project (Turtle)

# Add a library with the sources
add_library(${PROJECT_NAME} Turtle.cpp TileMap.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Turtle.hpp Turtle.cpp TileMap.hpp TileMap.cpp)
