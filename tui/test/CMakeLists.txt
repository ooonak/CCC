cmake_minimum_required(VERSION 3.22)

project(CccTuiUnitTests LANGUAGES CXX)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}
    TuiTests.cpp
    TuiHelpersTests.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${googletest_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  CCC::Tui
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

