# Galen Cochrane
# Copyright (C) 2016
# This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)

# No lesser version of cMake may be used.
cmake_minimum_required( VERSION 3.3 )

# Assign a project name
project( StringCount )

if( NOT WIN32 )
    # these are the compiler flags to be used on gcc
    set( CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS} -ggdb3     -Wall -std=c++11         " )
    set( CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS} -Ofast     -Wall -std=c++11 -DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS} -Og -ggdb3 -Wall -std=c++11 -DNDEBUG" )
endif()

set( LIBS         ${LIBS}         )
set( INCLUDE_DIRS ${INCLUDE_DIRS} )
set( SOURCE_FILES ${SOURCE_FILES}
        StringAnalyzer.cpp StringAnalyzer.h
        main.cpp
        )
include_directories( ${INCLUDE_DIRS} )
set( SOURCE_FILES ${SOURCE_FILES})
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )
target_link_libraries( ${PROJECT_NAME} ${LIBS} )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/strings
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/strings)