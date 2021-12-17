cmake_minimum_required(VERSION 3.12)

project(
    MyLogo
    VERSION 0.6
    DESCRIPTION "A simple Logo implementation in C++"
    HOMEPAGE_URL "https://github.com/DarkoGNU"
    LANGUAGES CXX
    )

# Unused for now
option(SELF_TEST "Enables testing code to be built" OFF)

# Set the C++ standard. LuaBridge (header-only library) won't compile with C++20
set(CMAKE_CXX_STANDARD 17)

# Add subfolders
add_subdirectory(Interpreter)
add_subdirectory(Main)
add_subdirectory(lib/LuaBridge)

# Other stuff
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(SELF_TEST)
	message(STATUS "Tests enabled")
    include(CTest)
	enable_testing()
endif()
