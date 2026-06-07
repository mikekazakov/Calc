cmake_minimum_required(VERSION 4.2)
project(Calc)
set(CMAKE_C_STANDARD 23)
add_executable(Calc
        app.c
)
#target_compile_features(calc PRIVATE
#    C_STANDARD 23
#)
#target_compile_options(calc PRIVATE
#    -nostdlib
#)
#
#target_link_options(calc PRIVATE
#    -nolibc
#)