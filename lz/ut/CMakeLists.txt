set(LZ_CH00_UT "ch00-lz-ut")

message(STATUS "Configuring target: ${LZ_CH00_UT}")

if(${WIN_CLANG})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
 /imsvc ${GOOGLETEST_INCLUDE_DIR} /imsvc ${GOOGLEMOCK_INCLUDE_DIR}\
 -Wno-weak-vtables")
else()
  include_directories(SYSTEM ${COMMON_INCLUDES})
endif()

add_executable(${LZ_CH00_UT}
  ../../gtest_main.cc
  ${LZ_ROOT}/ch00/ut.cpp)

target_link_libraries(${LZ_CH00_UT} gtest)
