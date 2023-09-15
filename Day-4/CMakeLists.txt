cmake_minimum_required(VERSION 3.26)
project(SDL2_TEST)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SDL2_TEST
        main.cpp
        Window_Object.cpp
        Window_Object.h
        Player_Object.cpp
        Player_Object.h
        Map_Object.cpp
        Map_Object.h)

target_link_libraries(SDL2_TEST -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)
