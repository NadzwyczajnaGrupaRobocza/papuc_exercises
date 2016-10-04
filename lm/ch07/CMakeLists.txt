include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../ch06)

add_executable(lm-ch07
  ../../gtest_main.cc
  EvaluatorTest-ch07-extensions.cpp
  ShuntingYardTest.cpp
  )

target_link_libraries(lm-ch07 lm-calculator-lib gtest gmock)
