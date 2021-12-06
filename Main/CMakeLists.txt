# Set the executable name
add_executable(${PROJECT_NAME} Main.cpp)

# Link the libraries
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC Turtle IO)
