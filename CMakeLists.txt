cmake_minimum_required(VERSION 3.10)
project(crossnative)
include_directories("include")

add_compile_definitions(CROSS_MODE_BUILD)


if (WIN32)
	add_library(crossnative SHARED src/win/common_win_impl.cc)
endif(WIN32)

if (UNIX AND NOT APPLE)
	add_library(crossnative SHARED src/linux/common_linux_impl.cc)
	target_link_libraries(crossnative X11)
endif(UNIX AND NOT APPLE)

if (APPLE)
	add_library(crossnative SHARED src/linux/common_apple_impl.cc)
endif(APPLE)

remove_definitions(CROSS_MODE_USE)
add_compile_definitions(CROSS_MODE_USE)
add_subdirectory("test")