cmake_minimum_required(VERSION 3.28.3)
project(OceanDepth C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES src/*/*.c)

add_executable(OceanDepth src/main.c
        ${SOURCES}
)
