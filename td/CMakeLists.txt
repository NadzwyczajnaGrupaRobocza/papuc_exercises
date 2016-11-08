add_subdirectory(test)
add_subdirectory(challenge260)

add_custom_target(${test}
  DEPENDS test-build
)
