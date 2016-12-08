include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lm-calculator-lib STATIC
  Token.cpp
  TokenStream.cpp
  Evaluator.cpp
  ExpressionSplitter.cpp
  )

add_executable(lm-ch06
  TokenStreamTest.cpp
  EvaluatorTest.cpp
  ExpressionSplitterTest.cpp
  )

target_link_libraries(lm-ch06 lm-calculator-lib lm-calculator-ext-lib gtest_main gmock)

add_executable(lm-calculator
  CalcMain.cpp
  )

target_link_libraries(lm-calculator lm-calculator-lib)

add_test(lm-ch06 ${EXECUTABLE_OUTPUT_PATH}/lm-ch06)
