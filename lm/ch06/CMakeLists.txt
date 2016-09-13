include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lm-calculator-lib STATIC
  Token.cpp
  TokenStream.cpp
  Evaluator.cpp
  ExpressionSplitter.cpp
  )

add_executable(lm-ch06
  ../../gtest_main.cc
  TokenStreamTest.cpp
  EvaluatorTest.cpp
  ExpressionSplitterTest.cpp
  )

target_link_libraries(lm-ch06 lm-calculator-lib gtest gmock)

add_executable(lm-calculator
  CalcMain.cpp
  )

target_link_libraries(lm-calculator lm-calculator-lib)
