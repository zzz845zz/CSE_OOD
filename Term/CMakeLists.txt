cmake_minimum_required(VERSION 3.0.0)
project(TextEditor VERSION 0.1.0)

include(CTest)
include_directories("${CMAKE_SOURCE_DIR}/include")
enable_testing()

add_executable(TextEditor main.cpp src/Line.cpp src/Editor.cpp src/UserInterface.cpp src/CommandIntepreter.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
