include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  test
    test.cpp
  )
target_link_libraries(test gtest_main)


add_custom_target(runTest
  COMMAND test
  COMMENT "Run test"
)
