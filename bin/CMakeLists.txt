cmake_minimum_required(VERSION 3.26)
project(labwork3_xocl404)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(labwork3_xocl404
        main.cpp
        parsing.cpp
        parsing.h
        sandpile.cpp
        sandpile.h
        bmp.cpp
        bmp.h)
