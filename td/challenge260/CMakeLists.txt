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

add_executable(td-challenge260
               main.cpp)

target_link_libraries(td-challenge260 libtd-challenge260)

#integration Test
add_custom_target(td-challenge260-test-run
	COMMAND "td-challenge260-test"
	COMMENT "Run test for challenge 260 for td")

add_custom_target(td-challenge260-prepare-integration-testrun
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/testSet ${CMAKE_BINARY_DIR}/bin
	COMMENT "Prepare for integration test for challange260")

add_custom_target(td-challenge260-integration-testrun)

add_custom_command(TARGET td-challenge260-integration-testrun
	COMMAND ./runChallenge260IntegrationTest.sh ./td-challenge260
	COMMENT "Run integration test for challange260"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_dependencies(td-challenge260-integration-testrun td-challenge260-prepare-integration-testrun)
add_dependencies(td-challenge260-integration-testrun td-challenge260)
