add_library(lm-ch290-lib STATIC
  InstructionLexer.cpp)

add_executable(lm-ch290-test
  InstructionLexerTest.cpp)

target_link_libraries(lm-ch290-test lm-ch290-lib gtest_main gmock)
