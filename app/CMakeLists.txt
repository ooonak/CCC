cmake_minimum_required(VERSION 3.22)

project(CCC LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE 
  CCC::MsgService
  CCC::Tui
)

if(EMSCRIPTEN)
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s FORCE_FILESYSTEM")
  #string(APPEND CMAKE_EXE_LINKER_FLAGS " -s WEBSOCKET_DEBUG")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -l websocket.js")

  foreach(file "index.html" "run_webassembly.py")
    configure_file("${file}" ${file})
  endforeach(file)
endif()

