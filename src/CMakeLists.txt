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

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)

FetchContent_Declare(
  msgpack
  GIT_REPOSITORY https://github.com/msgpack/msgpack-c.git
  GIT_TAG cpp-6.0.0
)

FetchContent_MakeAvailable(spdlog msgpack)

project(ccc LANGUAGES CXX VERSION 0.0.1)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE 
  ftxui::screen
  ftxui::dom
  ftxui::component
  spdlog::spdlog
  msgpack-cxx
)

