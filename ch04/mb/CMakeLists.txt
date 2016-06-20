include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-mb ../../gtest_main.cc empty.cpp)
target_link_libraries(ch04-mb gtest)


