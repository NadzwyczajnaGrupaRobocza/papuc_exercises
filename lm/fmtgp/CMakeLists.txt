add_executable(lm-fmtgp
  Ch04.test.cpp
  Ch07.test.cpp
  Ch11.test.cpp
  Ch12.test.cpp
  Rational.test.cpp
  gcd.test.cpp
  )

add_library(lm-fmtgp-lib STATIC
  Ch04.cpp
  Ch07.cpp
  Ch11.cpp
  Ch12.cpp
  gcd.cpp
  )

target_link_libraries(lm-fmtgp lm-fmtgp-lib gtest_main)

add_test(lm-fmtgp ${EXECUTABLE_OUTPUT_PATH}/lm-fmtgp)

add_executable(lm-fmtgp-bench
  Ch12.bench.cpp)

target_link_libraries(lm-fmtgp-bench lm-fmtgp-lib benchmark pthread)

add_executable(lm-fmtgp-ch13
  rsa.test.cpp)

add_library(lm-fmtgp-ch13-lib STATIC
  rsa.cpp)

target_link_libraries(lm-fmtgp-ch13
  lm-fmtgp-ch13-lib
  gtest_main)
