include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-lm ../../gtest_main.cc ex02.cpp ex05.cpp
  Expression.cpp
  ex08.cpp
  Grains.cpp)
target_link_libraries(ch04-lm gtest)


add_executable(ch04-05-UI Expression.cpp ex05-UI.cpp)
