# Set the project name
project (Interpreter)

# Add a library with the sources
add_library(${PROJECT_NAME} Interpreter.cpp)

# Add subfolders
add_subdirectory(Turtle)
add_subdirectory(IO)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Find LUA
FIND_PACKAGE(Lua 5.1 REQUIRED)
add_definitions(-DLUA)
include_directories(${LUA_INCLUDE_DIR})

# Link the libraries
target_link_libraries (${PROJECT_NAME} PUBLIC ${LUA_LIBRARY} Turtle IO LuaBridge)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Interpreter.cpp Parser.cpp)
