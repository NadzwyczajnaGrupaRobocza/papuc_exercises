include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(mb-05 ../../gtest_main.cc 
                     ../common/MB_Common.cpp
                     MB_05_UT.cpp
                     MB_05_02.cpp
                       )
target_link_libraries(mb-05 gtest)
