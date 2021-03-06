cmake_minimum_required (VERSION 2.8.11)

message(STATUS "Detected system with Microsoft compiler.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /Wall\
 /wd4251 /wd4265 /wd4350 /wd4371 /wd4514 /wd5031 /wd5026 /wd5027\
 /wd4625 /wd4619 /wd4626 /wd4710 /wd4711 /wd4820 /wd4668")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D not=! /D and=&& /D or=||")
