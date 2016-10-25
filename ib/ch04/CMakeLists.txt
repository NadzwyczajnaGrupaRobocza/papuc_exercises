include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-ib ch_04_05.cpp CalculatorTestSuite.cpp)
target_link_libraries(ch04-ib gtest_main)

add_custom_target(ch04-ib-ut-run
  COMMAND ch04-ib
  COMMENT "Run ch04-ib-ut"
)
