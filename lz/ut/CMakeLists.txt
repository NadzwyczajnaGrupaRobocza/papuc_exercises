set(LZ_CH00_UT "ch00-lz-ut")

include_directories(SYSTEM ${GOOGLETEST_INCLUDE_DIR})

add_executable(${LZ_CH00_UT}
  ../../gtest_main.cc
  ${LZ_ROOT}/ch00/ut.cpp)

target_link_libraries(${LZ_CH00_UT} gtest)
