set(EXECUTABLE_NAME lm-game03)
add_executable(${EXECUTABLE_NAME}
  main.cpp
  Board.cpp
  World.cpp
  PhysicalEntity.cpp
  QuantumField.cpp
  PointMass.cpp
  CollisionDetector.cpp)


target_compile_options(${EXECUTABLE_NAME} PRIVATE "-Wno-switch-enum")
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
