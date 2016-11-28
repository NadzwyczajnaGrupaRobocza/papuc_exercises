
add_executable(lm-game01
  main.cpp
  Board.cpp)
target_compile_options(lm-game01 PRIVATE "-Wno-switch-enum")
target_link_libraries(lm-game01 ${SFML_LIBRARIES})
