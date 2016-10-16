include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(mb-common Common_UT.cpp
                         Common.cpp
              	         )
target_link_libraries(mb-common gtest_main)

# Common
#add_executable(mb-common-bin MB_Common.cpp)
