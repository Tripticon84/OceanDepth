cmake_minimum_required(VERSION 4.0)
project(OceanDepth C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS src/include/*.h)
file(GLOB ALL src/*)

add_executable(OceanDepth src/main.c
        ${HEADERS}
        src/combat.c
        src/inventory.c
        src/map.c
        src/player.c
        src/save.c
        src/monsters.c
        src/display.c
        src/utils.c
        src/settings.c
)
