add_executable(mb-06 MB_06.cpp
                     ../common/Common.cpp
                     Token.cpp
                     TokenStream.cpp
                     Calculator.cpp)

add_executable(mb-06-ut Token.cpp
                        Calculator.cpp
                        ../common/Common.cpp
                        UTs.cpp)

target_link_libraries(mb-06-ut gtest_main gmock)
add_test(mb-06-ut ${EXECUTABLE_OUTPUT_PATH}/mb-06-ut)
