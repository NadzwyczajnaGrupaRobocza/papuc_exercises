include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(mb-04 ../../gtest_main.cc 
                     ../common/MB_Common.cpp
                     MB_04_UT.cpp
                     MB_04_10.cpp
                     MB_04_15.cpp
                     MB_04_02.cpp
                     MB_04_03.cpp
                     MB_04_05.cpp
                     MB_04_08.cpp)
target_link_libraries(mb-04 gtest)

add_executable(mb-test Test.cpp
                       MB_04_10.cpp)

# Chapter 04 Excercise 02
#add_executable(ch04-mb-02 ../../gtest_main.cc NGR_04_02_01.cpp NGR_04_02_UT.cpp)
add_executable(mb-04-02-bin MB_04_02.cpp MB_04_02_main.cpp)
#target_link_libraries(ch04-mb-02 gtest)

# Chapter 04 Excercise 03
#add_executable(ch04-mb-03 ../../gtest_main.cc NGR_04_03_01.cpp NGR_04_03_UT.cpp)
add_executable(mb-04-03-bin MB_04_03.cpp MB_04_03_main.cpp)
#target_link_libraries(ch04-mb-03 gtest)

# Chapter 04 Excercise 05
#add_executable(ch04-mb-05 ../../gtest_main.cc NGR_04_05_01.cpp NGR_04_05_UT.cpp)
add_executable(mb-04-05-bin MB_04_05.cpp MB_04_05_main.cpp)
#target_link_libraries(ch04-mb-05 gtest)

# Chapter 08 Excercise XX
#add_executable(ch04-mb-XX ../../gtest_main.cc NGR_04_XX_01.cpp NGR_04_XX_UT.cpp)
add_executable(mb-04-08-bin MB_04_08.cpp MB_04_08_main.cpp)
#target_link_libraries(ch04-mb-XX gtest)

## Chapter 04 Excercise XX
##add_executable(ch04-mb-XX ../../gtest_main.cc NGR_04_XX_01.cpp NGR_04_XX_UT.cpp)
#add_executable(ch04-mb-XX-bin NGR_04_XX_01.cpp NGR_04_XX_main.cpp)
##target_link_libraries(ch04-mb-XX gtest)

