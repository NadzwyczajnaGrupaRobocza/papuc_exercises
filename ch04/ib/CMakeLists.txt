include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-ib ../../gtest_main.cc empty.cpp)
target_link_libraries(ch04-ib gtest)


