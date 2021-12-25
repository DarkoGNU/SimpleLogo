cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Define the project
project(
    SimpleLogo
    VERSION 0.9
    DESCRIPTION "A simple Logo implementation in C++"
    HOMEPAGE_URL "https://github.com/DarkoGNU"
    LANGUAGES CXX
    )
    
# Some properties
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Unused for now
option(SELF_TEST "Enables testing code to be built" OFF)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add subfolders
add_subdirectory(Interpreter)
add_subdirectory(Main)

# Other stuff
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(SELF_TEST)
	message(STATUS "Tests enabled")
    include(CTest)
	enable_testing()
endif()
