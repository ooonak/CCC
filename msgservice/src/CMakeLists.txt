cmake_minimum_required(VERSION 3.22)

find_package(Threads)

include(FetchContent)

FetchContent_Declare(
    boost
    URL https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz
    URL_HASH SHA256=66a469b6e608a51f8347236f4912e27dc5c60c60d7d53ae9bfe4683316c6f04c
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0
)

set(msgpack_MSGPACK_CXX20 ON)
set(msgpack_MSGPACK_BUILD_DOCS OFF)

FetchContent_Declare(
  msgpack
  GIT_REPOSITORY https://github.com/msgpack/msgpack-c.git
  GIT_TAG cpp-6.0.0
)

FetchContent_MakeAvailable(boost spdlog msgpack)


project(MsgService VERSION 1.0.0 LANGUAGES CXX)

file(WRITE ${PROJECT_BINARY_DIR}/MsgServiceConfig.hpp.in "
#pragma once

#define MSGSERVICE_VERSION_MAJOR @MsgService_VERSION_MAJOR@
#define MSGSERVICE_VERSION_MINOR @MsgService_VERSION_MINOR@
#define MSGSERVICE_VERSION_PATCH @MsgService_VERSION_PATCH@
")

file(GLOB MESSAGE_SOURCES messages/*.cpp messages/*.hpp)

add_library(${PROJECT_NAME}
    include/msgservice/MsgService.hpp
    MsgService.cpp
    ${MESSAGE_SOURCES}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME}
   PRIVATE
   Threads::Threads
   spdlog::spdlog
   msgpack-cxx
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

add_library(CCC::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

configure_file("${PROJECT_BINARY_DIR}/MsgServiceConfig.hpp.in" MsgServiceConfig.hpp)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/msgservice
        DESTINATION include
        COMPONENT Devel
)

