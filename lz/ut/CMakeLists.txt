include_directories(SYSTEM ${GOOGLETEST_INCLUDE_DIR})

add_executable(ch00-lz-ut
  ${LZ_ROOT}/ch00/ut.cpp)

target_link_libraries(ch00-lz-ut gtest_main)

add_custom_target(ch00-lz-ut-run
  COMMAND ch00-lz-ut
  COMMENT "Run ch00-lz-ut"
)
