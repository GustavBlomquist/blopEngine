cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(BlopEngine)

# Add source files
file(
    GLOB_RECURSE SOURCE_FILES CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add headers from src
file(
    GLOB_RECURSE CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)

# Add directory to include path for compiler
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

# Define executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Create CMAKE_DIR to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")



# Add headers from libs
file(
    GLOB HEADER_LIB_DIRS CMAKE_CONFIGURE_DEPENDS 
    ${CMAKE_SOURCE_DIR}/libs/*
)

foreach(HEADER_LIB_DIR ${HEADER_LIB_DIRS})
    if(IS_DIRECTORY ${HEADER_LIB_DIR})
        # Extract library name from folder
        get_filename_component(LIB_NAME ${HEADER_LIB_DIR} NAME)

        # Create an interface target for the library
        add_library(${LIB_NAME} INTERFACE)

        # Add directory to include paths
        target_include_directories(${LIB_NAME} INTERFACE ${HEADER_LIB_DIR})

        # Link to executable
        target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
    endif() 
endforeach()

# Find pakages / install packages:

include(FetchContent)

# SDL2
find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
    message(STATUS "SDL2 found on the system.")
else()
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.10
    )
    FetchContent_MakeAvailable(SDL2)
endif()

# Lua

find_package(Lua REQUIRED)

if(Lua_FOUND)
    message(STATUS "Lua found on the system.")
else()
    FetchContent_Declare(
        Lua
        GIT_REPOSITORY https://github.com/lua/lua.git
        GIT_TAG v5.4.7 
    )
    FetchContent_MakeAvailable(Lua)
endif()



# Link SDL2 and Lua to executable
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main lua)


