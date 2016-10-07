set(LZ_ROOT ${CMAKE_CURRENT_LIST_DIR})

message(STATUS "Cmake build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_BINARY_DIR ./../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if(${WIN_CLANG})
  string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

message(STATUS "Cmake cxx flags release: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "Cmake cxx flags debug: ${CMAKE_CXX_FLAGS_DEBUG}")

if(${WIN_CLANG})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic\
 -Wno-c++98-c++11-compat-pedantic -Wno-undefined-func-template\
 -Wno-exit-time-destructors -Wno-global-constructors\
 -Wno-unknown-pragmas -Wno-missing-prototypes")
endif()

add_subdirectory(ch00)
add_subdirectory(ut)
