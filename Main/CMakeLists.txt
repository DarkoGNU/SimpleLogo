# Copyright 2021 The SimpleLogo Authors.
# Licensed under GPL-3.0-or-later

# Set the project name
project (Main)

# Add an executable and set its name
add_executable(${PROJECT_NAME} Main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME})

# Link the libraries
target_link_libraries (${PROJECT_NAME} PUBLIC Interpreter)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Main.cpp)
