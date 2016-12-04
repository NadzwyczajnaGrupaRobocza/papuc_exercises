
add_executable(lm-game02
  main.cpp
  Board.cpp
  World.cpp
  PhysicalEntity.cpp
  MassRegistry.cpp)

target_compile_options(lm-game02 PRIVATE "-Wno-switch-enum")
target_link_libraries(lm-game02 ${SFML_LIBRARIES})
