set(LZ_ROOT ${CMAKE_CURRENT_LIST_DIR})

message(STATUS "Cmake build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(ch00)
add_subdirectory(ut)

add_custom_target(${LZ-UT-RUN}
  DEPENDS ch00-lz-ut-run
)

#######################################

set(CLANG_COMPLETE "-D_MSC_VER=1900\n\
-I${GSL_INCLUDE_DIR}\n\
-I${GOOGLETEST_INCLUDE_DIR}\n\
-I${GOOGLEMOCK_INCLUDE_DIR}\n\
-std=c++14")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
STRING(REGEX REPLACE "-IC:/" "-Ic:/" CLANG_COMPLETE ${CLANG_COMPLETE})
endif()

file(WRITE ".clang_complete" ${CLANG_COMPLETE})
