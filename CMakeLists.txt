cmake_minimum_required(VERSION 3.28)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(sort_draw LANGUAGES CXX)

file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp)

add_executable(sort_draw ${sources})

target_include_directories(sort_draw PRIVATE src)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
    FIND_PACKAGE_ARGS 3 COMPONENTS Graphics)
FetchContent_MakeAvailable(SFML)

target_link_libraries(sort_draw SFML::Graphics)

target_compile_features(sort_draw PRIVATE cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(sort_draw PRIVATE -Wall -Wpedantic -Wextra)
elseif ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options(sort_draw PRIVATE /W4)
endif()
