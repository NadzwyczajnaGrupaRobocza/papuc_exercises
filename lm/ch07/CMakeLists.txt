include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../ch06)

add_library(lm-calculator-ext-lib STATIC
  ShuntingYard.cpp
  )

add_executable(lm-ch07
  ../../gtest_main.cc
  EvaluatorTest-ch07-extensions.cpp
  ShuntingYardTest.cpp
  )

target_link_libraries(lm-ch07 lm-calculator-ext-lib lm-calculator-lib gtest gmock)
