include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  td-test
    test.cpp
  )
target_link_libraries(td-test gtest_main)

add_test(td-test ${EXECUTABLE_OUTPUT_PATH}/td-test)
