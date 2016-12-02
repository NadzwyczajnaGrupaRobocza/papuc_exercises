include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch05-ib SquareEquation.cpp SquareEquationTest.cpp)
target_link_libraries(ch05-ib gtest_main)
add_test(ch05-ib ${EXECUTABLE_OUTPUT_PATH}/ch05-ib)