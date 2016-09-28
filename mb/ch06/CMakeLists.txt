add_executable(mb-06 MB_06.cpp
                     ../common/Common.cpp
                     Token.cpp
                     TokenStream.cpp
                     Calculator.cpp)

add_executable(mb-06-ut ../../gtest_main.cc
                        MockTokenStream.cpp
#                        Token.cpp
#                        TokenStream.cpp
                        UTs.cpp)

target_link_libraries(mb-06-ut gtest gmock)
