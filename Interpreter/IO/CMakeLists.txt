# Set the project name
project (IO)

# Add a library with the sources
add_library(${PROJECT_NAME} Params.cpp Writer.cpp)  

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# Link PNG++
if(PNG_FIND_QUIETLY)
    set(_FIND_ZLIB_ARG QUIET)
endif()
find_package(ZLIB ${_FIND_ZLIB_ARG})
find_package(PNG REQUIRED)

if(ZLIB_FOUND)
    find_path(PNG++_INCLUDE_DIR png.hpp /usr/local/include/png++ /usr/include/png++)

    set(PNG++_LIBRARIES ${PNG_LIBRARIES})

    if(PNG++_INCLUDE_DIR)
        set(PNG++_INCLUDE_DIRS ${PNG++_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})
        unset(PNG++_INCLUDE_DIR)
    endif()
endif()

# handle the QUIETLY and REQUIRED arguments and set PNG_FOUND to TRUE if
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PNG++ REQUIRED_VARS PNG++_INCLUDE_DIRS)
mark_as_advanced(PNG++_INCLUDE_DIRS)

#################################################################
# The code for finding PNG++ is from MRT CMake Modules
# Copyright 2002-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
#################################################################

include_directories(${PNG++_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})

# Set sources
target_sources(${PROJECT_NAME} PRIVATE Params.hpp Params.cpp Writer.hpp Writer.cpp)
