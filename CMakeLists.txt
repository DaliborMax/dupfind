cmake_minimum_required(VERSION 3.16)
project(dupfind VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(DUPFIND_BUILD_TESTS "Build unit tests" ON)

file(GLOB DUPFIND_SOURCES src/*.cpp)
add_library(dupfind_core ${DUPFIND_SOURCES})

target_include_directories(dupfind_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(dupfind_core PRIVATE /W4)
else()
    target_compile_options(dupfind_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(dupfind app/main.cpp)
target_link_libraries(dupfind PRIVATE dupfind_core)

if(DUPFIND_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()