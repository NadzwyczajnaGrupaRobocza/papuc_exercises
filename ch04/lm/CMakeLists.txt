cmake_minimum_required (VERSION 2.8.11)
project("PaPuC")

#add_subdirectory(googletest)

# add_executable(gtesttest gtest_main.cc sample1_unittest.cc sample1.cc)

# target_link_libraries(gtesttest LINK_PUBLIC gtest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c++14")

#add_executable(exercise1 training.cpp exercise2.cpp gtest_main.cc)
#target_link_libraries(exercise1 LINK_PUBLIC gtest)

add_executable(ex04 test.cpp)
