add_executable(mb_Leds main.cpp
                       LedCommon.cpp
                       InputParser.cpp
                       LedBlinker.cpp
                       InstructionPreparer.cpp)

add_executable(mb_Leds_UT LedsUT.cpp
                          LedCommon.cpp
                          InputParser.cpp
                          LedBlinker.cpp
                          InstructionPreparer.cpp)

target_link_libraries(mb_Leds_UT gtest_main gmock)
