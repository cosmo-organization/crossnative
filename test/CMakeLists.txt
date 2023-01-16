cmake_minimum_required(VERSION 3.10)

project(test)

include_directories("include")

add_executable(fuzzytest fuzzytest.cc)

target_link_libraries(fuzzytest crossnative)