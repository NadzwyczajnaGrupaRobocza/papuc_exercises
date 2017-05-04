add_subdirectory(ch04)
add_subdirectory(ch05)
add_subdirectory(ch06)
add_subdirectory(ch07)

add_subdirectory(dprog)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "6.3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
    message("We have shiny new compiler, we'll use some concepts")
  endif()
endif()

add_subdirectory(fmtgp)

if(SFML_FOUND)
add_subdirectory(game01)
add_subdirectory(game02)
add_subdirectory(game03)
endif()

add_subdirectory(range-playground)

add_subdirectory(chunk-eater)
add_subdirectory(adapter-types)
