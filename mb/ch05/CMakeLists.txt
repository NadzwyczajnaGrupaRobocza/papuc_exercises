include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(mb-ch05 ../../gtest_main.cc 
                       ../common/MB_Common.cpp
                       NGR_05_UT.cpp
                       NGR_05_02_01.cpp
                       )
target_link_libraries(mb-ch05 gtest)
