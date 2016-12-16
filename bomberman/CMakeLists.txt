add_executable(bomberman
  main.cpp
  Board.cpp
  World.cpp)

target_link_libraries(bomberman ${SFML_LIBRARIES})
