add_library(lm-ch290-lib STATIC
  InstructionLexer.cpp
  Processor.cpp)

add_executable(lm-ch290-test
  InstructionLexerTest.cpp
  ProcessorTest.cpp)

target_link_libraries(lm-ch290-test lm-ch290-lib gtest_main gmock)

add_executable(lm-ch290
  main.cpp)

target_link_libraries(lm-ch290 lm-ch290-lib)
