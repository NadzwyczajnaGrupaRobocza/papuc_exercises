include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ch04-mb-02 ../../gtest_main.cc NGR_04_02_01.cpp NGR_04_02_UT.cpp)
add_executable(ch04-mb-02-bin NGR_04_02_01.cpp NGR_04_02_main.cpp)

add_executable(ch04-mb-03 ../../gtest_main.cc NGR_04_03_01.cpp NGR_04_03_UT.cpp)
add_executable(ch04-mb-03-bin NGR_04_03_01.cpp NGR_04_03_main.cpp)

target_link_libraries(ch04-mb-02 gtest)
target_link_libraries(ch04-mb-03 gtest)

