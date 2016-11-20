add_library(libtd-challenge260 STATIC
            InstructionLexer.cpp
	    SemanticAnalyser.cpp
	    LedController.cpp
	    )

add_executable(td-challenge260-test
               InstructionLexerTest.cpp
	       SemanticAnalyserTest.cpp
	       LedControllerTest.cpp
	       )

target_link_libraries(td-challenge260-test libtd-challenge260 gtest_main gmock)

add_custom_target(td-challenge260-test-run
	COMMAND "td-challenge260-test"
	COMMENT "Run test for challenge 260 for td")
