cmake_minimum_required(VERSION 3.22)

project(CCC)

option(EMSCRIPTEM "Build WebAssembly version" OFF)
option(BUILD_TESTS "Build test programs" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT EMSCRIPTEN)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
endif()

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(msgservice)
add_subdirectory(tui)
add_subdirectory(app)

