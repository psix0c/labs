cmake_minimum_required(VERSION 4.0)
project(_12_ C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(save_stars save_stars.c)
add_executable(load_and_draw_stars load_and_draw_stars.c)