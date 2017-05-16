add_subdirectory(test)
add_subdirectory(challenge260)
add_subdirectory(scheme-hello-world)

if(SFML_FOUND)
add_subdirectory(game03)
endif()
