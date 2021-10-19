cmake_minimum_required(VERSION 3.17)

# "Build everything" project, intended for CI (e.g. it does not take care about assets altogether).
project(jiji-all)
include(cmake/common.cmake)

# Third-party location
# We have these in common.cmake, but they have an extra `..`.
include_directories("./third-party/include")
link_directories("./third-party/lib-vs")


# Don't use individual's project roots, go to `source` directly.
add_subdirectory(jiji/source jiji-lib)
include_directories(jiji/source)

add_subdirectory(demo-template/source jiji-demo-template)