set(LZ_ROOT ${CMAKE_CURRENT_LIST_DIR})

message(STATUS "Cmake build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(290_blinking_leds)

add_custom_target(${LZ-UT-RUN}
  DEPENDS 290_blinking_leds-lz-ut-run
)
