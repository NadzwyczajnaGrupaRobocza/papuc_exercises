include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-mb-UT ../../gtest_main.cc NGR_04_02_UT.cpp)
add_executable(ch04-mb NGR_04_02_01.cpp)

target_link_libraries(ch04-mb-UT gtest)
