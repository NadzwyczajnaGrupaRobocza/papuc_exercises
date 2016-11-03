add_subdirectory(test)

add_custom_target(${test}
  DEPENDS test-build
)
