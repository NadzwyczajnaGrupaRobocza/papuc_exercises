add_library(290_blinking_leds-lz-lib STATIC
  Private/LedToken.cpp
  Private/LedTokenState.cpp
  Private/RecognizeState.cpp
  Private/LedLdState.cpp
  Private/LedOutState.cpp
  Private/LedSimulationFsm.cpp
  Private/LedSimulation.cpp
  Private/Byte.cpp
  Private/Memory.cpp
  Private/BlinkingLeds.cpp
  )

target_include_directories(290_blinking_leds-lz-lib PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Public
)

add_executable(290_blinking_leds-lz
  main.cpp
  )

add_executable(290_blinking_leds-lz-ut
  Test/UniqueMockTest.cpp
  Test/LedTokenTest.cpp
  Test/LedSimulationFsmTest.cpp
  Test/LedLdStateTest.cpp
  Test/LedOutStateTest.cpp
  Test/ByteTest.cpp
  Test/MemoryTest.cpp
  Test/LedSimulationTest.cpp
  Test/RecognizeStateTest.cpp
  Test/BlinkingLedsTest.cpp
  )

target_include_directories(290_blinking_leds-lz-ut PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Private
)

target_link_libraries(290_blinking_leds-lz 290_blinking_leds-lz-lib)
target_link_libraries(290_blinking_leds-lz-ut 290_blinking_leds-lz-lib gtest_main gmock)

add_test(290_blinking_leds-lz-ut ${EXECUTABLE_OUTPUT_PATH}/290_blinking_leds-lz-ut)
