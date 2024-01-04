cmake_minimum_required(VERSION 3.28)

project(borderless)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

include_directories(include)

set(SOURCES
    src/borderless.cpp
)

add_executable(borderless_debug ${SOURCES})
set_target_properties(borderless_debug PROPERTIES OUTPUT_NAME "borderless")
set_target_properties(borderless_debug PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})

add_executable(borderless_release ${SOURCES})
set_target_properties(borderless_release PROPERTIES OUTPUT_NAME "borderless")
set_target_properties(borderless_release PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

target_link_libraries(borderless_release -static)