cmake_minimum_required(VERSION 3.22)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.1.1
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


project(Tui VERSION 0.0.1 LANGUAGES CXX)

file(WRITE ${PROJECT_BINARY_DIR}/tuiconfig.hpp.in "
#pragma once

#define TUI_VERSION_MAJOR @TUI_VERSION_MAJOR@
#define TUI_VERSION_MINOR @TUI_VERSION_MINOR@
#define TUI_VERSION_PATCH @TUI_VERSION_PATCH@
")

add_library(${PROJECT_NAME}
    include/tui/tui.hpp
    tui.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
   PRIVATE
   ftxui::screen
   ftxui::dom
   ftxui::component
)

add_library(CCC::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

configure_file("${PROJECT_BINARY_DIR}/tuiconfig.hpp.in" tuiconfig.hpp)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/dp
        DESTINATION include
        COMPONENT Devel
)

