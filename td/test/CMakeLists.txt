include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  td-test
    test.cpp
  )
target_link_libraries(td-test gtest_main)


add_custom_target(runTest
  COMMAND td-test
  COMMENT "Run test"
)
