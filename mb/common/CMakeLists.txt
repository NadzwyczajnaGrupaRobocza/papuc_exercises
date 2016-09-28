include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(mb-common ../../gtest_main.cc 
                         Common_UT.cpp
                         Common.cpp
              	         )
target_link_libraries(mb-common gtest)

# Common
#add_executable(mb-common-bin MB_Common.cpp)
