include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-lm ../../gtest_main.cc ex02.cpp)
target_link_libraries(ch04-lm gtest)


