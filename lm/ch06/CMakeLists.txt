include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lm-calculator-lib STATIC
  Token.cpp
  TokenStream.cpp
  Evaluator.cpp
  ExpressionSplitter.cpp
  ShuntingYard.cpp
  )

add_executable(lm-ch06
  TokenStreamTest.cpp
  EvaluatorTest.cpp
  ExpressionSplitterTest.cpp
  )

target_link_libraries(lm-ch06 lm-calculator-lib gtest_main gmock_main)

add_executable(lm-calculator
  CalcMain.cpp)

target_link_libraries(lm-calculator lm-calculator-lib)
