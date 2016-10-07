cmake_minimum_required (VERSION 2.8.11)
project("PaPuC++")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows" AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(WIN_CLANG "yes")
endif()

if(${WIN_CLANG})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

add_subdirectory(googletest)

set(GOOGLETEST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/include/")
set(GOOGLEMOCK_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googlemock/include/")
set(GSL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/GSL/")

set(COMMON_INCLUDES ${GOOGLETEST_INCLUDE_DIR} ${GOOGLEMOCK_INCLUDE_DIR})

if(${WIN_CLANG})
  message(STATUS "Detected Windows system with clang compiler.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -Weverything /imsvc ${GSL_INCLUDE_DIR}")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pedantic -g")
  include_directories(${GSL_INCLUDE_DIR})
endif()

add_subdirectory(ch04)
add_subdirectory(mb)
add_subdirectory(lm)
add_subdirectory(ib)
add_subdirectory(lz)
