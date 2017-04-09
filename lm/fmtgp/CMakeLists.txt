add_executable(lm-fmtgp Ch04.test.cpp Ch07.test.cpp)

add_library(lm-fmtgp-ch04 STATIC
  Ch04.cpp
  Ch07.cpp
  )

target_link_libraries(lm-fmtgp lm-fmtgp-ch04 gtest_main)

add_test(lm-fmtgp ${EXECUTABLE_OUTPUT_PATH}/lm-fmtgp)

