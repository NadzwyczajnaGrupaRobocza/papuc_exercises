add_subdirectory(ch04)
add_subdirectory(ch05)

add_custom_target(${IB-UT-RUN}
  DEPENDS ch04-ib-ut-run ch05-ib-ut-run
)
