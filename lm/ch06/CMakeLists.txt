include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lm-ch06
  ../../gtest_main.cc
  ex_base.cpp
  Token.cpp
  TokenStream.cpp
  Evaluator.cpp
  )
target_link_libraries(lm-ch06 gtest)
