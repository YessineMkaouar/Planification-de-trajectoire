cmake_minimum_required(VERSION 3.21)
project(SIM202)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SIM202
        main.cpp
        trajectoire.cpp
        trajectoire.hpp
        )
