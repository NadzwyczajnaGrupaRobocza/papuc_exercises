add_executable(mb_Leds main.cpp
                       InputParser.cpp
                       LedBlinker.cpp)

add_executable(mb_Leds_UT LedsUT.cpp
                          InputParser.cpp
                          LedBlinker.cpp)

target_link_libraries(mb_Leds_UT gtest_main gmock)
