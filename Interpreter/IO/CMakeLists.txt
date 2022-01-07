# Set the project name
project (IO)

# Add a library with the sources
add_library(${PROJECT_NAME} Params.cpp Writer.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Params.hpp Params.cpp Writer.hpp Writer.cpp)

# Link PNG++
find_package(PNG++ REQUIRED)
include_directories(${PNG++_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PNG++_LIBRARIES})
