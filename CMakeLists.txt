cmake_minimum_required(VERSION 3.10)

project(scrollcat LANGUAGES CXX VERSION 0.1.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

add_executable(scrollcat main.cpp)
add_library(game game.cpp)
add_library(window window.cpp)

target_link_libraries(window game SDL2::SDL2)
target_link_libraries(scrollcat window)

target_include_directories(scrollcat PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            )

