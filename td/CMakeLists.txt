add_subdirectory(test)
add_subdirectory(challenge260)

add_custom_target(${test}
  DEPENDS test-build
)

add_custom_target(${TD-UT-RUN}
	          DEPENDS td-challenge260-test-run
	          )
