add_library(physics-lib STATIC
  Physics/Private/Collision.cpp)

target_include_directories(physics-lib PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Physics/Public
  ${CMAKE_CURRENT_LIST_DIR}/Bomberman/Public
  )

add_executable(bomberman
  Bomberman/Private/Bomberman.cpp
  Bomberman/Private/Entity.cpp
  Bomberman/Private/Board.cpp)

target_include_directories(bomberman PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Bomberman/Public
  )


target_link_libraries(bomberman physics-lib ${SFML_LIBRARIES})
