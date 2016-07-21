include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(mb-04 ../../gtest_main.cc 
                     ../common/MB_Common.cpp
                     MB_04_UT.cpp
                     MB_04_10.cpp
                     MB_04_15.cpp
                     )
target_link_libraries(mb-04 gtest)

add_executable(mb-test Test.cpp
                       MB_04_10.cpp
                       )
