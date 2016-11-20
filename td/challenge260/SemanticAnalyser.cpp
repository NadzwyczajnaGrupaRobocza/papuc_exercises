#include "SemanticAnalyser.hpp"

Instructions SemanticAnalyser::analyse(const Tokens& tokens)
{
  if (tokens.empty())
  {
    return {};
  }
  Instructions instructions;
  unsigned alreadyProcessedTokens = 0;
  while (tokens.size() - alreadyProcessedTokens % sizeOfInstruction && tokens.size() != alreadyProcessedTokens)
  {
    if (areTokensValidLdInstruction(tokens.cbegin() + alreadyProcessedTokens))
    {
      instructions.push_back( {InstructionType::LdA, 0});
    }
    else if (areTokensValidOutInstruction(tokens.cbegin() + alreadyProcessedTokens))
    {
      instructions.push_back( {InstructionType::OutA, 0});
    }
    else
    {
      throw InvalidSemantic {"Invalid instruction"};
    }
    alreadyProcessedTokens += sizeOfInstruction;
  }
  return instructions;
}

bool SemanticAnalyser::areTokensValidOutInstruction(Tokens::const_iterator begin)
{
  return (begin++)->type == TokenType::Out
      && (begin++)->type == TokenType::ZeroWithBrackets
      && (begin++)->type == TokenType::A;
}

bool SemanticAnalyser::areTokensValidLdInstruction(Tokens::const_iterator begin)
{
  return (begin++)->type == TokenType::Ld
      && (begin++)->type == TokenType::A
      && (begin++)->type == TokenType::Number8Bit;
}
