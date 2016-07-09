include_directories(${COMMON_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

# UT
add_executable(ch04-mb ../../gtest_main.cc 
                       NGR_04_UT.cpp
                       NGR_04_02_01.cpp
                       NGR_04_03_01.cpp
                       NGR_04_05_01.cpp
                       NGR_04_08_01.cpp)
target_link_libraries(ch04-mb gtest)

# Chapter 04 Excercise 02
#add_executable(ch04-mb-02 ../../gtest_main.cc NGR_04_02_01.cpp NGR_04_02_UT.cpp)
add_executable(ch04-mb-02-bin NGR_04_02_01.cpp NGR_04_02_main.cpp)
#target_link_libraries(ch04-mb-02 gtest)

# Chapter 04 Excercise 03
#add_executable(ch04-mb-03 ../../gtest_main.cc NGR_04_03_01.cpp NGR_04_03_UT.cpp)
add_executable(ch04-mb-03-bin NGR_04_03_01.cpp NGR_04_03_main.cpp)
#target_link_libraries(ch04-mb-03 gtest)

# Chapter 04 Excercise 05
#add_executable(ch04-mb-05 ../../gtest_main.cc NGR_04_05_01.cpp NGR_04_05_UT.cpp)
add_executable(ch04-mb-05-bin NGR_04_05_01.cpp NGR_04_05_main.cpp)
#target_link_libraries(ch04-mb-05 gtest)

# Chapter 08 Excercise XX
#add_executable(ch04-mb-XX ../../gtest_main.cc NGR_04_XX_01.cpp NGR_04_XX_UT.cpp)
add_executable(ch04-mb-08-bin NGR_04_08_01.cpp NGR_04_08_main.cpp)
#target_link_libraries(ch04-mb-XX gtest)

