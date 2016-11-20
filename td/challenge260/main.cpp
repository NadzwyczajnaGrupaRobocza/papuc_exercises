#include "InstructionLexer.hpp"
#include "SemanticAnalyser.hpp"
#include "LedController.hpp"

#include <iostream>

int main()
{
  InstructionLexer lexer;
  SemanticAnalyser analyser;
  LedController ledConteoller(std::cout);

  std::string input;
  while (std::getline(std::cin, input))
  {
    const auto tokens = lexer.parseInstructions(input);
    const auto instrucions = analyser.analyse(tokens);
    ledConteoller.runProgram(instrucions);
  }
  return 0;
}