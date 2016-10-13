cmake_minimum_required (VERSION 2.8.11)
project("PaPuC++")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows" AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(WIN_CLANG "yes")
endif()

if(${WIN_CLANG})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations\
 -Wno-c++98-compat -Wno-c++98-compat-pedantic\
 -Wno-c++98-c++11-compat-pedantic -Wno-undefined-func-template\
 -Wno-exit-time-destructors -Wno-global-constructors\
 -Wno-unknown-pragmas -Wno-missing-prototypes -Wno-undef\
 -Wno-language-extension-token -Wno-missing-noreturn -Wno-missing-noreturn\
 -Wno-language-extension-token -Wno-used-but-marked-unused\
 -Wno-shift-sign-overflow -Wno-deprecated\
 -Wno-weak-vtables -Wno-sign-conversion")

  string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

add_subdirectory(googletest)

set(GOOGLETEST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/include/")
set(GOOGLEMOCK_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/googletest/googlemock/include/")
set(GSL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/GSL/")

set(COMMON_INCLUDES ${GOOGLETEST_INCLUDE_DIR} ${GOOGLEMOCK_INCLUDE_DIR})

if(${WIN_CLANG})
  message(STATUS "Detected Windows system with clang compiler.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-compatibility-version=19 -m64\
 -Weverything /imsvc ${GSL_INCLUDE_DIR}")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
-Wall \
-Wextra \
-Wnon-virtual-dtor \
-std=c++14 \
-pedantic \
-g \
-Werror=pedantic")
  include_directories(${GSL_INCLUDE_DIR})
endif()

add_subdirectory(mb)
add_subdirectory(lm)
add_subdirectory(ib)
add_subdirectory(lz)
