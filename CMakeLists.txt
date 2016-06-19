cmake_minimum_required (VERSION 2.8.11)
project("PaPuC++")

add_subdirectory(googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c++14")
set(GOOGLETEST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/include/")
set(GOOGLEMOCK_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googlemock/include/")
set(COMMON_INCLUDES ${GOOGLETEST_INCLUDE_DIR} ${GOOGLEMOCK_INCLUDE_DIR})

add_subdirectory(ch04)

# add_executable(gtesttest gtest_main.cc sample1_unittest.cc sample1.cc)

# target_link_libraries(gtesttest LINK_PUBLIC gtest)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c++14")

# add_executable(example example1.cpp gtest_main.cc)
# target_link_libraries(example gtest)
