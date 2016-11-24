add_subdirectory(common)

add_subdirectory(ch04)
add_subdirectory(ch05)
add_subdirectory(ch06)
add_subdirectory(Leds)

add_custom_target(${MB-UT-RUN}
  DEPENDS ch04-mb-ut-run ch05-mb-ut-run
)
