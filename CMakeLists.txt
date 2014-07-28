cmake_minimum_required(VERSION 2.8.12)

#
#   First some setup
#

set(SE_THIRD_PARTY_DIR  ${CMAKE_SOURCE_DIR}/vendor)

set(CMAKE_MODULE_PATH "${SE_THIRD_PARTY_DIR}/cmake/Modules")

message(STATUS "CMAKE_MODULE_PATH     = ${CMAKE_MODULE_PATH}")

include(SEFunctions)

init_vars()

add_subdirectory(DeferredShading)