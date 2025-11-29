
cmake_minimum_required(VERSION 3.10)

project(mini_file_editor_lib C)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c")

add_library(mini_file_editor_lib STATIC ${SOURCES})
