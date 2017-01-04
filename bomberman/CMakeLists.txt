add_library(physics-lib STATIC
  Physics/Private/Collision.cpp
  Physics/Private/Collider.cpp)

target_include_directories(physics-lib PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Physics/Public
  ${CMAKE_CURRENT_LIST_DIR}/Bomberman/Public
  )

add_executable(bomberman
  Bomberman/Private/Bomberman.cpp
  Bomberman/Private/Entity.cpp
  Bomberman/Private/Board.cpp
  Bomberman/Private/TouchAlert.cpp)

target_include_directories(bomberman PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Bomberman/Public
  )

target_link_libraries(bomberman physics-lib ${SFML_LIBRARIES})

add_executable(bomberman-physics-ut
  Physics/Test/ColliderTest.cpp
  )
target_include_directories(bomberman-physics-ut PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Physics/Private
  )
target_link_libraries(bomberman-physics-ut physics-lib gtest_main)
add_test(bomberman-physics-ut ${EXECUTABLE_OUTPUT_PATH}/bomberman-physics-ut)
