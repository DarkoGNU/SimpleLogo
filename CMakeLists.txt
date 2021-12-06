cmake_minimum_required(VERSION 3.12)

project(
    MyLogo
    DESCRIPTION "A simple Logo implementation in C++"
    HOMEPAGE_URL "https://github.com/DarkoGNU"
    LANGUAGES CXX
    )

# Unused for now
option(SELF_TEST "Enables testing code to be built" OFF)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add subfolders
add_subdirectory(Turtle)
add_subdirectory(IO)
add_subdirectory(Main)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(SELF_TEST)
	message(STATUS "Tests enabled")
    include(CTest)
	enable_testing()
endif()
