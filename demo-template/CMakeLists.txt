cmake_minimum_required(VERSION 3.17)

project(jiji-demo-template)
include(../cmake/common.cmake)


# The library.
add_subdirectory(../jiji/source jiji-lib)
include_directories(../jiji/source)


# The executable.
add_subdirectory(source jiji-demo-template)
jiji_startup(jiji-demo-template)
