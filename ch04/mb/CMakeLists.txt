include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-mb ../../gtest_main.cc NGR_04_02_01.cpp NGR_04_02_UT.cpp)
add_executable(ch04-mb-bin NGR_04_02_01.cpp NGR_04_02_main.cpp)

target_link_libraries(ch04-mb gtest)
