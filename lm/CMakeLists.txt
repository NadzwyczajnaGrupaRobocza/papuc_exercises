add_subdirectory(ch04)
add_subdirectory(ch05)
add_subdirectory(ch06)
add_subdirectory(ch07)

add_custom_target(${LM-UT-RUN}
  DEPENDS ch04-lm-ut-run ch06-lm-ut-run
)
