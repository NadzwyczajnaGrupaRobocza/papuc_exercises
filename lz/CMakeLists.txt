set(LZ_ROOT ${CMAKE_CURRENT_LIST_DIR})

message(STATUS "Cmake build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(ch00)
add_subdirectory(ut)

add_custom_target(${LZ-UT-RUN}
  DEPENDS ch00-lz-ut-run
)
