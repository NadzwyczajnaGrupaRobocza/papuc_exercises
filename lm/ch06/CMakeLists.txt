include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lm-ch06
  TokenStreamTest.cpp
  Token.cpp
  TokenStream.cpp
  Evaluator.cpp
  EvaluatorTest.cpp
  ExpressionSplitter.cpp
  ExpressionSplitterTest.cpp
  )

target_link_libraries(lm-ch06 gtest_main gmock)

add_executable(calc
  CalcMain.cpp
  Token.cpp
  TokenStream.cpp
  Evaluator.cpp
  ExpressionSplitter.cpp
  )

add_custom_target(ch06-lm-ut-run
  COMMAND lm-ch06
  COMMENT "Run ch06-lm-ut"
)
