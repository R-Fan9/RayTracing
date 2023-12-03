cmake_minimum_required(VERSION 3.26)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES main.cpp glad.c)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

add_executable(RayTracing ${SOURCE_FILES})

target_link_libraries(RayTracing glfw)
