cmake_minimum_required (VERSION 2.8.11)
project("PaPuC++")

add_subdirectory(googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c++14")
set(GOOGLETEST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/include/")
set(GOOGLEMOCK_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googlemock/include/")
set(COMMON_INCLUDES ${GOOGLETEST_INCLUDE_DIR} ${GOOGLEMOCK_INCLUDE_DIR})

add_subdirectory(ch04)
add_subdirectory(mb)
add_subdirectory(lm)
add_subdirectory(ib)