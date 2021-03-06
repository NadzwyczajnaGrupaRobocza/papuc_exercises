cmake_minimum_required (VERSION 2.8.11)

message(STATUS "Detected system with Gcc compiler.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wall \
-Wextra \
-Wconversion \
-Wfloat-equal \
-Wunreachable-code \
-Wswitch-enum \
-Wshadow \
-Wnon-virtual-dtor \
-std=c++14 \
-pedantic \
-g \
-Werror")
