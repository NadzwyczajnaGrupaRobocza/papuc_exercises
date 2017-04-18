add_library(lm-adapter-types-lib STATIC
  array_adapter.cpp)

add_executable(lm-adapter-types-test
  array_adapter.test.cpp)

target_link_libraries(lm-adapter-types-test
  lm-adapter-types-lib
  gtest_main)
