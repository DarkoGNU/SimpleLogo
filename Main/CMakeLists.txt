# Set the project name
project (Main)

# Set the executable name
add_executable(${PROJECT_NAME} Main.cpp)

# Link the libraries
target_link_libraries (${PROJECT_NAME} PUBLIC Interpreter)

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Main.cpp)
