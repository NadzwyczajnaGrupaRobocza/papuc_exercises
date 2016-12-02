include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-ib ch_04_05.cpp CalculatorTestSuite.cpp)
target_link_libraries(ch04-ib gtest_main)
add_test(ch04-ib ${EXECUTABLE_OUTPUT_PATH}/ch04-ib)
