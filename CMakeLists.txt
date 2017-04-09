cmake_minimum_required (VERSION 2.8.11)
project("PaPuC++")

enable_testing()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(RANGEV3_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/range-v3/include")
set(PAPUC_COMMON_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/common/include")
set(GSL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/GSL/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGSL_THROW_ON_CONTRACT_VIOLATION")

find_package(SFML 2 COMPONENTS system window graphics network audio)

add_subdirectory(external/googletest)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  include(${CMAKE_SOURCE_DIR}/cmakes/platforms/Windows.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/cmakes/platforms/Linux.cmake)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  include(${CMAKE_SOURCE_DIR}/cmakes/compilators/Clang.cmake)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  include(${CMAKE_SOURCE_DIR}/cmakes/compilators/Msvc.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/cmakes/compilators/Gcc.cmake)
endif()

if(SFML_FOUND)
  include_directories(SYSTEM ${SFML_INCLUDE_DIR})
endif()

include_directories(SYSTEM ${GSL_INCLUDE_DIR})
include_directories(SYSTEM ${RANGEV3_INCLUDE_DIR})
include_directories(${PAPUC_COMMON_INCLUDE_DIR})

add_subdirectory(mb)
add_subdirectory(lm)
add_subdirectory(ib)
add_subdirectory(lz)
add_subdirectory(td)
