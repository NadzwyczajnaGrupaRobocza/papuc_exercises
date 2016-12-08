add_executable(mb_Leds main.cpp
                       LedCommon.cpp
                       InstructionConverter.cpp
                       LedBlinker.cpp
                       InstructionParser.cpp)

add_executable(mb_Leds_UT LedsUT.cpp
                          LedCommon.cpp
                          InstructionConverter.cpp
                          LedBlinker.cpp
                          InstructionParser.cpp)

target_link_libraries(mb_Leds_UT gtest_main gmock)
