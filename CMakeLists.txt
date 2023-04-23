cmake_minimum_required(VERSION 3.24)
project(3DViewerCpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/model)

add_executable(3DViewerCpp
        src/model/debug.cc
        src/model/model.cc
        src/model/model.h)
