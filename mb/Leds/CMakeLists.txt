add_executable(mb_Leds main.cpp
                       InputParser.cpp
                       InstructionToLedBlinkConverter.cpp
                       LedBlinker.cpp)

add_executable(mb_Leds_UT LedsUT.cpp
                          InputParser.cpp
                          InstructionToLedBlinkConverter.cpp
                          LedBlinker.cpp)

target_link_libraries(mb_Leds_UT gtest_main gmock)
