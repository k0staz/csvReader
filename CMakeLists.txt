cmake_minimum_required(VERSION 3.17)
project(csvreader)

set(CMAKE_CXX_STANDARD 17)

add_executable(csvreader main.cpp table.cpp table.h)