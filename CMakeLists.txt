cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(BlopEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Copy assets to build directory.
# file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
# I'm figuring out how I'll handle assets

# Add source files
file(
    GLOB_RECURSE SOURCE_FILES CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Define executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

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
        target_include_directories(${LIB_NAME} INTERFACE ${HEADER_LIB_DIR}/..)

        # Link to executable
        target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
    endif() 
endforeach()

# Find pakages / install packages:

include(FetchContent)

# SDL2
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.10
    )
    FetchContent_MakeAvailable(SDL2)
else()
    message(STATUS "SDL2 found on the system: ${SDL2_INCLUDE_DIRS}, ${SDL2_LIBRARIES}")
endif()

# Detect if SDL2 exists in both brew and framework
set(SDL2_BREW_FOUND OFF)
set(SDL2_FRAMEWORK_FOUND OFF)

if(EXISTS "/usr/local/include/SDL2/SDL.h" AND EXISTS "/usr/local/lib/linSDL2.dylib")
    set(SDL2_BREW_FOUND ON)
endif()

if(EXISTS "/Library/Frameworks/SDL2.framework")
    set(SDL2_FRAMEWORK_FOUND ON)
endif()

# Prioritize homebrew if both are found
if(SDL2_BREW_FOUND AND SDL2_FRAMEWORK_FOUND)
    message(STATUS "SDL2 detected in both brew and framwork paths. Prioritizing brew path")
    target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include/SDL2)
    target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib)
elseif(SDL2_FRAMEWORK_FOUND)
    message(STATUS "Using SDL2 Framework version")
    target_include_directories(${PROJECT_NAME} PRIVATE /Library/Frameworks/SDL2.framework/Headers)
    target_link_directories(${PROJECT_NAME} PRIVATE "-framework SDL2")
else()
    message(STATUS "Using SDL2 configuration from find_package")
endif()

# SDL2_image
find_package(SDL2_image REQUIRED)
if(NOT SDL2_image_FOUND)
    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.3
    )
    FetchContent_MakeAvailable(SDL2_image)
else()
    message(STATUS "SDL2_image found on the system.")
endif()

# SDL2_ttf
find_package(SDL2_ttf REQUIRED)
if(NOT SDL2_ttf_FOUND)
    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.8.0
    )
    FetchContent_MakeAvailable(SDL2_ttf)
else()
    message(STATUS "SDL2_ttf found on the system.")
endif()

# SDL2_mixer
find_package(SDL2_mixer REQUIRED)
if(NOT SDL2_mixer_FOUND)
    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.0
    )
    FetchContent_MakeAvailable(SDL2_mixer)
else()
    message(STATUS "SDL2_mixer found on the system.")
endif()


# Lua

find_package(Lua REQUIRED)

if(NOT Lua_FOUND)
    FetchContent_Declare(
        Lua
        GIT_REPOSITORY https://github.com/lua/lua.git
        GIT_TAG v5.4.7 
    )
    FetchContent_MakeAvailable(Lua)
else()
    message(STATUS "Lua found on the system.")
endif()


# Link SDL2 and Lua to executable
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR}/.. ${LUA_INCLUDE_DIR})
target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE SDL2::SDL2 
    SDL2::SDL2main 
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    ${LUA_LIBRARIES}
)
