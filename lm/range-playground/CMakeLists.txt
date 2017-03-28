if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set_source_files_properties(plaything_1.cpp PROPERTIES COMPILE_FLAGS -Wno-error)
endif()

add_executable(plaything_1
  plaything_1.cpp)
