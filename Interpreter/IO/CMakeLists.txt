# Copyright 2021 The SimpleLogo Authors.
# Licensed under GPL-3.0-or-later

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
include_directories(${PNG++_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})
add_definitions(${PNG_DEFINITIONS})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})
